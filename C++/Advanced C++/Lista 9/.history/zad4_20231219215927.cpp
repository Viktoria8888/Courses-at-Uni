#include <iostream>
#include <filesystem>
#include <algorithm>
using namespace std;
int main()
{

    std::cout << "Enter the path: ";
    std::string directoryPath;
    std::getline(std::cin, directoryPath);

    std::filesystem::path canonicalPath = std::filesystem::canonical(directoryPath);
    std::cout << "Canonical path " << canonicalPath << "\n\n";

    if (!std::filesystem::exists(canonicalPath))
    {
        std::cerr << "Directory doesn't exists\n";
        return 1;
    }

    for (const auto &entry : std::filesystem::directory_iterator(canonicalPath))
    {
        if (entry.is_directory())
        {
            std::cout << "[Directory] " << entry.path().filename() << "\n";
        }
    }

    for (const auto &entry : std::filesystem::directory_iterator(canonicalPath))
    {
        if (entry.is_regular_file())
        {
            std::cout << "[File] " << entry.path().filename() << "\n";
        }
    }

    return 0;
}
// /home/viktoria/Downloads
