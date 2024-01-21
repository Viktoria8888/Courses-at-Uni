


#include "Wrappers.h"

void writeRandomIntegers(const std::string& filename, int count) {
    try {
        OutputFile outputFile(filename);

        for (int i = 0; i < count; ++i) {
            int num = std::rand();
            outputFile.write(num);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void readAndPrintFile(const std::string& filename) {
    try {
        InputFile inputFile(filename);

        while (!inputFile.eof()) {
            unsigned char byte;
            inputFile.read(byte);
            if (byte >= 32 && byte <= 126) {
                std::cout << "Char: " << byte << std::endl;
            }

            std::cout << "Hex: 0x" << std::hex << static_cast<int>(static_cast<unsigned char>(byte)) << std::endl;

            std::cout << "Dec: " << static_cast<int>(static_cast<unsigned char>(byte)) << std::endl;
            std::cout<<std::endl;

        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    const std::string filename = "data5.bin";
    const int numberOfRandomNumbers = 100;

    writeRandomIntegers(filename, numberOfRandomNumbers);
    readAndPrintFile(filename);

    return 0;
}
