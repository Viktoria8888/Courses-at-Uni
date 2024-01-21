#include <iostream>
#include <filesystem>
#include <algorithm>
namespace fs = std::filesystem;
using namespace std;

int main()
{

    cout << "Enter the path: ";
    string directoryPath;
    getline(std::cin, directoryPath);

    fs::path canonicalPath = std::filesystem::canonical(directoryPath);

    if (!fs::exists(canonicalPath))
    {
        std::cerr << "Directory doesn't exists\n";
        return 1;
    }
    uint64_t total = 0;
    for (const auto &entry : fs::recursive_directory_iterator(canonicalPath))
    {
        if (entry.is_regular_file())
        {
            total += entry.file_size();}
    }
    cout<<"The sum of the sizes of files: "<<total<<"bytes"<<endl;


    return 0;
}
// /home/viktoria/Downloads
