#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <html_file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::copy(
        std::istream_iterator<std::string>(inputFile),
        std::istream_iterator<std::string>(),
        std::back_inserter(lines));

    inputFile.close();

    // Define a more flexible regex pattern for detecting hyperlinks
    std::regex rgx("<a[^>]*\\s+href=['\"]([^'\"]+)['\"][^>]*>");

    // Iterate through the lines and search for hyperlinks
    for (const std::string &line : lines) {
        std::smatch match;
        if (std::regex_search(line, match, rgx)) {
            // Print the content of the href attribute
            std::cout << match[1] << std::endl;
        }
    }

    return 0;
}
