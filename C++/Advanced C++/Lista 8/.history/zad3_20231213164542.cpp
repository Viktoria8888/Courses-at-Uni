#include <iostream>
#include <regex>

int main() {
    std::string text;
    std::cin>>text;

    std::regex rgx("^([[:upper:]][[:alpha:]]*((-|[[:space:]])[[:upper:]][[:alpha:]]*)*)$");

    bool isMatch = std::regex_match(text, rgx);


    std::cout << "Is match: " << isMatch << std::endl;

    return 0;
}
