//
// Created by viktoria on 22.05.23.
//

#include "Wrappers.h"

InputFile::InputFile(const std::string &filename) : file(filename, std::ios::binary) {
    if (!file) {
        throw std::runtime_error("Failed to open input file");
    }
    file.exceptions(std::ios::failbit | std::ios::badbit);
}

OutputFile::OutputFile(const std::string &filename) : file(filename, std::ios::binary) {
    if (!file) {
        throw std::runtime_error("Failed to open output file");
    }
    file.exceptions(std::ios::failbit | std::ios::badbit);
}

