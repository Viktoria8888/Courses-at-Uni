#include <iostream>
#include <fstream>
#include <string>

// Funkcja do serializacji obiektów na strumień binarny
template <typename T>
void serialize(std::ostream& stream, const T& data) {
    stream.write(reinterpret_cast<const char*>(&data), sizeof(data));
}

// Funkcja do deserializacji obiektów ze strumienia binarnego
template <typename T>
void deserialize(std::istream& stream, T& data) {
    stream.read(reinterpret_cast<char*>(&data), sizeof(data));
}

// Funkcja do serializacji std::string
void serializeString(std::ostream& stream, const std::string& str) {
    size_t size = str.size();
    serialize(stream, size);
    stream.write(str.c_str(), size);
}

// Funkcja do deserializacji std::string
void deserializeString(std::istream& stream, std::string& str) {
    size_t size;
    deserialize(stream, size);
    char* buffer = new char[size + 1]; // +1 for null terminator
    stream.read(buffer, size);
    buffer[size] = '\0';
    str = buffer;
    delete[] buffer;
}

// Funkcja do serializacji tablicy
template <typename T>
void serializeArray(std::ostream& stream, const T* array, size_t size) {
    serialize(stream, size);
    for (size_t i = 0; i < size; ++i) {
        serialize(stream, array[i]);
    }
}

// Funkcja do deserializacji tablicy
template <typename T>
std::pair<T*, size_t> deserializeArray(std::istream& stream) {
    size_t size;
    deserialize(stream, size);
    T* array = new T[size];
    for (size_t i = 0; i < size; ++i) {
        deserialize(stream, array[i]);
    }
    return {array, size};
}

int main() {
    // Przykładowe dane do serializacji
    bool boolValue = true;
    char charValue = 'A';
    short shortValue = 12345;
    int intValue = 987654321;
    long long longLongValue = 1234567890123456789LL;
    float floatValue = 3.14f;
    double doubleValue = 2.71828;
    long double longDoubleValue = 3.14159265358979323846L;
    std::string stringValue = "Hello, World!";
    int intArray[] = {1, 2, 3, 4, 5};

    // Serializacja danych do pliku
    std::ofstream outFile("serialized_data.bin", std::ios::binary);
    serialize(outFile, boolValue);
    serialize(outFile, charValue);
    serialize(outFile, shortValue);
    serialize(outFile, intValue);
    serialize(outFile, longLongValue);
    serialize(outFile, floatValue);
    serialize(outFile, doubleValue);
    serialize(outFile, longDoubleValue);
    serializeString(outFile, stringValue);
    serializeArray(outFile, intArray, sizeof(intArray) / sizeof(int));
    outFile.close();

    // Deserializacja danych z pliku
    std::ifstream inFile("serialized_data.bin", std::ios::binary);
    bool deserializedBool;
    char deserializedChar;
    short deserializedShort;
    int deserializedInt;
    long long deserializedLongLong;
    float deserializedFloat;
    double deserializedDouble;
    long double deserializedLongDouble;
    std::string deserializedString;
    auto [deserializedIntArray, arraySize] = deserializeArray<int>(inFile);
    inFile.close();

    // Wyświetlanie zdeserializowanych danych
    std::cout << "Deserialized Bool: " << deserializedBool << std::endl;
    std::cout << "Deserialized Char: " << deserializedChar << std::endl;
    std::cout << "Deserialized Short: " << deserializedShort << std::endl;
    std::cout << "Deserialized Int: " << deserializedInt << std::endl;
    std::cout << "Deserialized Long Long: " << deserializedLongLong << std::endl;
    std::cout << "Deserialized Float: " << deserializedFloat << std::endl;
    std::cout << "Deserialized Double: " << deserializedDouble << std::endl;
    std::cout << "Deserialized Long Double: " << deserializedLongDouble << std::endl;
    std::cout << "Deserialized String: " << deserializedString << std::endl;
    std::cout << "Deserialized Int Array: ";
    for (size_t i = 0; i < arraySize; ++i) {
        std::cout << deserializedIntArray[i] << " ";
    }
    std::cout << std::endl;

    // Zwolnienie pamięci po tablicy
    delete[] deserializedIntArray;

    return 0;
}
