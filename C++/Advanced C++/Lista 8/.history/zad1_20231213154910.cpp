#include <iostream>
#include <regex>

int main() {
    std::string time1 = "14:17";
    // std::cin >> time;
    std::string rgx = std::regex("^([0-1]?[0-9]|2[0-3]):[0-5][0-9](:[0-5][0-9])?$");
    bool is_correct = std::regex_match(time,rgx);
    std::cout << is_correct << std::endl;

    return 0;
}
