#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <utility>

inline std::istream &clearline(std::istream &is) {
    char c;
    while (is.get(c) && c != '\n') {

    }
    return is;
}

struct ignore {
    int count;

    ignore(int x) : count(x) {}

    friend std::istream& operator>>(std::istream& is, const ignore& manip) {
        char c;
        int ignored = 0;
        while (ignored < manip.count && is.get(c) && c != '\n') {
            ignored++;
        }
        return is;
    }
};


// Manipulator bezparametrowy dla strumienia wyjściowego - comma
inline std::ostream &comma(std::ostream &os) {
    os << ", ";
    return os;
}

// Manipulator bezparametrowy dla strumienia wyjściowego - colon
std::ostream &colon(std::ostream &os) {
    os << ": ";
    return os;
}

// Manipulator z parametrem dla strumienia wyjściowego - index
struct index {
    int value;
    int width;

    index(int x, int w) : value(x), width(w) {}

    friend std::ostream& operator<<(std::ostream& os, const index& manip) {
        return os << "[" << std::setw(manip.width) << manip.value << "]";
    }
};

int main() {
//    Testing clearline
//    std::cout << "Enter a line of text: ";
//    std::cin >> clearline;
//--------------------------------------------------------------
//    Testing ignore(x)
//    std::cout << "Enter a line of text: ";
//    std::cin >> ignore(5);  // Skip the next 5 characters from input
//
//    std::string line;
//    std::cin >> line;
//
//    std::cout << "Word entered after ignoring: " << line << std::endl;
//---------------------------------------------------------------
//    Testing index
//    int x = 42;
//    int width = 6;
//
//    std::cout << "Value with index: " << index(x, width) << std::endl;
//
//    return 0;



    std::vector<std::pair<std::string , int>> lines;
    std::string line;
    int lineCount = 1;

    while (std::getline(std::cin, line))

    {
        lines.emplace_back(line, lineCount);
        lineCount++;
    }

    std::sort(lines.begin(), lines.end());

    for (const auto& pair : lines) {
        std::cout <<index(pair.second, 3)<<pair.first<<std::endl;
    }

    return 0;
}
