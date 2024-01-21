#include <iostream>
#include <regex>
using namespace std;

int main() {
    std::string time = "14:17";
    // std::cin>>time;
    bool is_correct = regex_match(time,
    regex("[0-23]:[0-59]?(:[0-59])"));
    std
    return 0;
}
