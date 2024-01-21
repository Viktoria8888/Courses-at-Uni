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


#include <fstream>
#include <string>
#include <iostream>

template<typename T, size_t N>
struct array_in_file {
    std::fstream file;
    std::string filename;

    array_in_file() : filename("array_data.bin") {
        // Open the file for reading and writing in binary mode
        file.open(filename, std::ios::out | std::ios::binary);  // First, open for writing to create the file
        file.close();  // Close to flush and ensure file is created
        file.open(filename, std::ios::in | std::ios::out | std::ios::binary);  // Reopen for both reading and writing

        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for array_in_file.");
        }
    }

    ~array_in_file() {
        if (file.is_open()) {
            file.close();  // Ensure the file is closed
        }
    }

    void write_to_file(const T (&arr)[N]) {
        if (!file.is_open() || !file.good()) {
            throw std::runtime_error("File is not open or in a bad state.");
        }

        file.seekp(0, std::ios::beg);  // Go to the beginning of the file
        file.write(reinterpret_cast<const char*>(arr), N * sizeof(T));

        if (!file.good()) {
            throw std::runtime_error("Error occurred during file write operation.");
        }

        file.flush();  // Ensure that changes are written to the file
    }

    void read_from_file(T (&arr)[N]) {
        if (!file.is_open() || !file.good()) {
            throw std::runtime_error("File is not open or in a bad state.");
        }

        file.seekg(0, std::ios::beg);  // Go to the beginning of the file
        file.read(reinterpret_cast<char*>(arr), N * sizeof(T));

        if (!file.good()) {
            throw std::runtime_error("Error occurred during file read operation.");
        }
    }
};




template<typename T, size_t N>
struct arr_holder {
    static const size_t Threshold = 1024 * 1024; // Define a threshold for small and large arrays
    using type = typename std::conditional<
        sizeof(T) * N <= Threshold,
        array_on_heap<T, N>,
        array_in_file<T, N>
    >::type;
    type value;

    // Proxy methods to write and read from file if type is array_in_file
    void write_to_file(const T (&arr)[N]) {
        if constexpr (std::is_same_v<type, array_in_file<T, N>>) {
            value.write_to_file(arr);
        } else {
            std::cerr << "write_to_file is only applicable for large arrays stored in files." << std::endl;
        }
    }

    void read_from_file(T (&arr)[N]) {
        if constexpr (std::is_same_v<type, array_in_file<T, N>>) {
            value.read_from_file(arr);
        } else {
            std::cerr << "read_from_file is only applicable for large arrays stored in files." << std::endl;
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

    arr_holder<int, 1024 * 1024 + 1> largeArray;
    int testArray[1024 * 1024 + 1];
    for (int i = 0; i < 1024 * 1024 + 1; ++i) {
        testArray[i] = i;
    }

    largeArray.write_to_file(testArray);
    largeArray.read_from_file(testArray);

    return 0;
}
