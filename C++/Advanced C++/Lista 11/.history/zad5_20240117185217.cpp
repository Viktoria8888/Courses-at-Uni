#include <iostream>
#include <string>
#include <type_traits>
#include <fstream>
using namespace std;


template <typename T>
struct on_stack
{
    T data;
    T *operator->() { return &data; }
    T &operator*() { return data; }
};

template <typename T>
struct on_heap
{
    T *data;
    on_heap() : data() { data = new T(); }
    ~on_heap() { delete data; }
    T *operator->() { return data; }
    T &operator*() { return *data; }
};

template <typename T>
struct obj_holder
{
    using type = typename conditional<(sizeof(T) <= sizeof(std::string) &&
                                            !std::is_array<T>::value),
                                           on_stack<T>, on_heap<T>>::type;
    type value;
};

template <typename T, size_t N>
struct array_on_heap
{
    T *data;
    array_on_heap() : data(new T[N]) {}
    ~array_on_heap() { delete[] data; }
    T &operator[](size_t i) { return data[i]; }
};


#include <fstream>
#include <string>
#include <iostream>

template<typename T, size_t N>
struct array_in_file {
    std::fstream file;
    std::string filename;

    array_in_file() : filename("array_data.bin") {

        file.open(filename, std::ios::out | std::ios::binary);
        file.close();
        file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    }

    ~array_in_file() {
        if (file.is_open()) {
            file.close();
        }
    }

    void write_to_file(const T (&arr)[N]) {

        file.seekp(0, std::ios::beg);
        file.write(reinterpret_cast<const char*>(arr), N * sizeof(T));

        if (!file.good()) {
            throw std::runtime_error("Error occurred during file write operation.");
        }

        file.flush();
    }

    void read_from_file(T (&arr)[N]) {
        if (!file.is_open()) {
            throw std::runtime_error("File is not open.");
        }

        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char*>(arr), N * sizeof(T));


    }
};




template<typename T, size_t N>
struct arr_holder {
    static const size_t Threshold = 1024 //sizeof(string);
    using type = typename std::conditional<
        sizeof(T) * N <= Threshold,
        array_on_heap<T, N>,
        array_in_file<T, N>
    >::type;
    type value;

    void write_to_file(const T (&arr)[N]) {
        if constexpr (std::is_same_v<type, array_in_file<T, N>>) {
            value.write_to_file(arr);}

    }

    void read_from_file(T (&arr)[N]) {
        if constexpr (std::is_same_v<type, array_in_file<T, N>>) {
            value.read_from_file(arr);
        }
    }
};



struct LargeData
{
    int array[1000];
};

int main()
{
    obj_holder<int> smallObj;
    *smallObj.value = 42;
    std::cout << "Small Object: " << *smallObj.value << std::endl;

    obj_holder<LargeData> largeObj;
    largeObj.value->array[0] = 100;
    std::cout << "Large Object First Element: " << largeObj.value->array[0] << std::endl;

    arr_holder<int, 10> smallArray;
    smallArray.value[0] = 1;
    std::cout << "Small Array First Element: " << smallArray.value[0] << std::endl;

    arr_holder<int, 1024 + 1> largeArray;
    int testArray[1024  + 1];
    int readArray[1024 + 1];
    for (int i = 0; i < 1024  + 1; ++i) {
        testArray[i] = i;
    }

    largeArray.write_to_file(testArray);
    largeArray.read_from_file(readArray);
    for (int i = 0; i< 1024 + 1; i++){
        cout<<readArray[i]<<endl;
    }


    return 0;
}
