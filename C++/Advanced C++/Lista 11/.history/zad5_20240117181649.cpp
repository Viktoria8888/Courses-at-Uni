#include <iostream>
#include <string>
#include <type_traits>
#include <fstream>

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
    using type = typename std::conditional<(sizeof(T) <= sizeof(std::string) &&
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
template <typename T, size_t N>
struct array_in_file
{
    std::fstream file;
    std::string filename;

    array_in_file() : filename("array_data.txt"), file(filename, std::ios::in | std::ios::out | std::ios::trunc) {
        if (!file) {
            std::cerr << "Could not open file for array_in_file." << std::endl;
            exit(1);
        }

        T defaultObject = T();
        for (size_t i = 0; i < N; ++i) {
            file << defaultObject << std::endl;
        }
    }

    ~array_in_file() {
        file.close();
    }
    T operator[](size_t i) {
        if (i >= N) {
            std::cerr << "Index out of bounds in array_in_file." << std::endl;
            exit(1);
        }
        file.seekg(std::ios::beg); // Go to the beginning of the file
        T value;
        for (size_t idx = 0; idx <= i; ++idx) {
            file >> value;
        }
        return value;
    }

};

template <typename T, size_t N>
struct arr_holder
{
    static const size_t Threshold = 1024;
    using type = typename std::conditional<(sizeof(T) * N <= Threshold), array_on_heap<T, N>, array_in_file<T, N>>::type;
    type value;
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

    arr_holder<int, 5000> largeArray;
    largeArray[0] = 2;
    // Note: array_in_file is not fully implemented, so this is just a conceptual test
    // std::cout << "Large Array First Element: " << largeArray.value[0] << std::endl;

    return 0;
}
