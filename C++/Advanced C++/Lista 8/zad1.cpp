#include <iostream>
#include <regex>

int main() {
    std::string time1 = "14:17";
    std::string time2 = "09:15";
    std::string time3 = "23:37:08";
    std::string time4 = "14.16";
    std::string time5 = "19:5";
    // std::cin >> time;
    std::regex rgx("^([0-1]?[0-9]|2[0-3]):[0-5][0-9](:[0-5][0-9])?$");
    std::cout << std::regex_match(time1,rgx) << std::endl;
    std::cout << std::regex_match(time2,rgx) << std::endl;
    std::cout << std::regex_match(time3,rgx) << std::endl;
    std::cout << std::regex_match(time4,rgx) << std::endl;
    std::cout << std::regex_match(time5,rgx) << std::endl;

    return 0;
}
