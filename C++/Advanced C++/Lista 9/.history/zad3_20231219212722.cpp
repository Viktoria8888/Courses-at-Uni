#include <ctime> // for std::asctime
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <format>
namespace fs = std::filesystem;

using namespace std;

void displayFileAttributes(const fs::path &filePath)
{
    cout << "File attributes for: " << filePath << endl;

    if (fs::exists(filePath))
    {
        cout << "Canonical path: " << fs::canonical(filePath) << endl;

        // Convert file_time_type to std::time_t for output streamin

        // Output the modified time using std::asctime
        std::cout << std::format("File write time is {}\n", ftime);

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
