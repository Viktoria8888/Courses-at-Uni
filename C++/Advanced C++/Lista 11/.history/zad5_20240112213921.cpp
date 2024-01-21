#include <iostream>
#include <string>
#include <type_traits>
#include <fstream>

template<typename T>
struct on_stack {
    T data;
    T* operator->() { return &data; }
    T& operator*() { return data; }
};

template<typename T>
struct on_heap {
    T* data;
    on_heap() : data(new T) {}
    ~on_heap() { delete data; }
    T* operator->() { return data; }
    T& operator*() { return *data; }
};

template<typename T>
struct obj_holder {
    using type = typename std::conditional<(sizeof(T) <= sizeof(std::string) &&
                         !std::is_array<T>::value), on_stack<T>, on_heap<T>>::type;
    type value;
};


template<typename T, size_t N>
struct array_on_heap {
    T* data;
    array_on_heap() : data(new T[N]) {}
    ~array_on_heap() { delete[] data; }
    T& operator[](size_t i) { return data[i]; }
};

template<typename T, size_t N>
struct array_in_file {

    std::fstream file;
    array_in_file() {
        // Otwórz plik i zainicjuj tablicę
    }
    ~array_in_file() {
        // Zamknij plik
    }
    T operator[](size_t i) {
        // Implementacja indeksowania pliku
    }
};

template<typename T, size_t N>
struct arr_holder {
    static const size_t Threshold = 1024;
    using type = typename std::conditional<(sizeof(T) * N <= Threshold), array_on_heap<T, N>, array_in_file<T, N>>::type;
    type value;
};

struct LargeData {
    int array[1000]; // Large data to ensure it gets stored on the heap
};

int main() {
    obj_holder<int> smallObj;
    *smallObj.value = 42; // Corrected usage
    std::cout << "Small Object: " << *smallObj.value << std::endl;

    obj_holder<LargeData> largeObj;
    largeObj.value->array[0] = 100; // Corrected usage
    std::cout << "Large Object First Element: " << largeObj.value->array[0] << std::endl;

    return 0;
}

