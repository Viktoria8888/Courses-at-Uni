#include <iostream>
#include <string>
#include <cstring>

class SerializerDeserializer {
public:

    template<typename T>
    static void serialize(std::ostream& stream, const T& data) {
        stream.write(reinterpret_cast<const char*>(&data), sizeof(T));
    }


    template<typename T>
    static void deserialize(std::istream& stream, T& data) {
        stream.read(reinterpret_cast<char*>(&data), sizeof(T));
    }


    static void serialize(std::ostream& stream, const std::string& str) {
        size_t size = str.size();
        serialize(stream, size);
        stream.write(str.c_str(), size);
    }


    static void deserialize(std::istream& stream, std::string& str) {
        size_t size;
        deserialize(stream, size);

        char* buffer = new char[size + 1];
        stream.read(buffer, size);
        buffer[size] = '\0';  // Null-terminate the string
        str = buffer;
        delete[] buffer;
    }

    template<typename T>
    static void serialize(std::ostream& stream, const T* array, size_t size) {
        serialize(stream, size);
        for (size_t i = 0; i < size; ++i) {
            serialize(stream, array[i]);
        }
    }


    template<typename T>
    static std::pair<T*, size_t> deserializeArray(std::istream& stream) {
        size_t size;
        deserialize(stream, size);

        T* array = new T[size];
        for (size_t i = 0; i < size; ++i) {
            deserialize(stream, array[i]);
        }

        return std::make_pair(array, size);
    }
};

int main() {

    int intValue = 42;
    std::string stringValue = "Hello, World!";
    double doubleValue = 3.14;

    SerializerDeserializer::serialize(std::cout, intValue);
    SerializerDeserializer::serialize(std::cout, stringValue);
    SerializerDeserializer::serialize(std::cout, doubleValue);

    int deserializedInt;
    std::string deserializedString;
    double deserializedDouble;

    SerializerDeserializer::deserialize(std::cin, deserializedInt);
    SerializerDeserializer::deserialize(std::cin, deserializedString);
    SerializerDeserializer::deserialize(std::cin, deserializedDouble);

    std::cout << "Deserialized int: " << deserializedInt << std::endl;
    std::cout << "Deserialized string: " << deserializedString << std::endl;
    std::cout << "Deserialized double: " << deserializedDouble << std::endl;


    int intArray[] = {1, 2, 3, 4, 5};
    size_t arraySize = sizeof(intArray) / sizeof(int);


    SerializerDeserializer::serialize(std::cout, intArray, arraySize);

    std::pair<int*, size_t> deserializedIntArray = SerializerDeserializer::deserializeArray<int>(std::cin);

    std::cout << "Deserialized int array: ";
    for (size_t i = 0; i < deserializedIntArray.second; ++i) {
        std::cout << deserializedIntArray.first[i] << " ";
    }
    std::cout << std::endl;

    delete[] deserializedIntArray.first;

    return 0;
}
