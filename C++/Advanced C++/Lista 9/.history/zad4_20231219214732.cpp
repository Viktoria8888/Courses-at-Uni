#include <iostream>
#include <filesystem>
#include <algorithm>
using namespace std;
int main() {

    std::cout << "Podaj sciezke do katalogu: ";
    std::string directoryPath;
    std::getline(std::cin, directoryPath);

    try {
        std::filesystem::path canonicalPath = std::filesystem::canonical(directoryPath);
        std::cout << "Nazwa kanoniczna katalogu: " << canonicalPath << "\n\n";


        if (!std::filesystem::exists(canonicalPath)) {
            std::cerr << "Podany katalog nie istnieje.\n";
            return 1;
        }


        for (const auto& entry : std::filesystem::directory_iterator(canonicalPath)) {
            if (entry.is_directory()) {
                std::cout << "[Katalog] " << entry.path().filename() << "\n";
            }
        }


        for (const auto& entry : std::filesystem::directory_iterator(canonicalPath)) {
            if (entry.is_regular_file()) {
                std::cout << "[Plik] " << entry.path().filename() << "\n";
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Błąd: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
