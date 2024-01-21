#include <iostream>
#include <regex>

int main() {
    std::string time = "14:17";
    // std::cin >> time;

    bool is_correct = std::regex_match(time, std::regex("^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$"));
    std::cout << is_correct << std::endl;

    return 0;
}
