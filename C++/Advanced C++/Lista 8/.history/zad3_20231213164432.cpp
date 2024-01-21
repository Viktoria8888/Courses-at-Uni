#include <iostream>
#include <regex>

int main() {
    std::string text = "Zielona Gora-Goralska Biala";


    std::regex rgx("^([[:upper:]][[:alpha:]]*((-|[[:space:]])[[:upper:]][[:alpha:]]*)?)$");

    bool isMatch = std::regex_match(text, rgx);


    std::cout << "Is match: " << isMatch << std::endl;

    return 0;
}
