#include <iostream>
#include <regex>
using namespace std;

int main() {
    int day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    std::string date;
    std::cin>>date;
    std::smatch match;
    std::regex rgx("^(([0-1][0-9]|2[0-9]|3[0-1])-(0[0-9]|1[0-2])-(\\d{4}))$");
    if (std::regex_match(date, match, rgx)) {

        if (std::stoi(match[1].str()) <= day[std::stoi(match[2].str())]){
            std::cout<<"Valid"<<std::endl;
        }
        else{
            std::cout<<"wrong date"<<std::endl;
        }

    } else {
        std::cout << "Invalid date format" << std::endl;
    }

    return 0;
}
