#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>


namespace fs = std::filesystem;

using namespace std;
using namespace chrono_literals;

void displayFileAttributes(const fs::path &filePath)
{
    cout << "File attributes for: " << filePath << endl;

    if (fs::exists(filePath))
    {
        cout << "Canonical path: " << fs::canonical(filePath) << endl;

        // auto lastModifiedTime = std::filesystem::last_write_time(filePath);

        // auto lastModifiedTimeT = std::chrono::system_clock::to_time_t(lastModifiedTime);

        cout << "Size: " << fs::file_size(filePath) << " bytes" << endl;
    }
    else
    {
        cout << "File not found." << endl;
    }

    cout << "--------------------------" << endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <file1> [file2] [file3] ..." << endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i)
    {
        fs::path filePath(argv[i]);
        displayFileAttributes(filePath);
    }

    return 0;
}
