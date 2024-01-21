//
// Created by viktoria on 22.05.23.
//

#ifndef LISTA_10_WRAPPERS_H
#define LISTA_10_WRAPPERS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <random>


class InputFile {
private:
    std::ifstream file;

public:
    InputFile(const std::string& filename);
    ~InputFile() { file.close();}

    // istream & read(char *gdzie, streamsize ile)
    template <typename T>
    void read(T& data) {
        file.read(reinterpret_cast<char*>(&data), sizeof(T));
        if (!file) {
            throw std::runtime_error("Failed to read from input file");
        }
    }

    bool eof() {
        return file.eof();
    }
};


class OutputFile {
private:
    std::ofstream file;

public:
    OutputFile(const std::string& filename);
    ~OutputFile() {file.close();}


    template <typename T>
    void write(const T& data) {
        file.write(reinterpret_cast<const char*>(&data), sizeof(T));
        if (!file) {
            throw std::runtime_error("Failed to write to output file");
        }
    }
};


#endif //LISTA_10_WRAPPERS_H
