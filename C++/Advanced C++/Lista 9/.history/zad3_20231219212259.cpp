#include <iostream>
#include <filesystem>
#include <iomanip>

namespace fs = std::filesystem ;

void displayFileAttributes(const fs::path& filePath) {
    std::cout << "File attributes for: " << filePath << std::endl;


        if (fs::exists(filePath)) {
            std::cout << "Canonical path: " << fs::canonical(filePath) << std::endl;
            std::cout << "Last modified time: " << fs::last_write_time(filePath) << std::endl;
            std::cout << "Size: " << fs::file_size(filePath) << " bytes" << std::endl;
        } else {
            std::cout << "File not found." << std::endl;
        }


    std::cout << "--------------------------" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file1> [file2] [file3] ..." << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        fs::path filePath(argv[i]);
        displayFileAttributes(filePath);
    }

    return 0;
}
