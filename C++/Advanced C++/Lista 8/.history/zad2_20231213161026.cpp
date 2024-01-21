#include <iostream>
#include <regex>
using namespace std;

int main() {
    std::string time;
    std::cin>>time;
    std::regex rgx("^(([0-1][0-9]|2[0-9]|3[0-1])-(0[0-9]|1[0-2])-\d{4})$");
    cout<<regex_match(time,rgx)<<std::endl;
    return 0;
}
