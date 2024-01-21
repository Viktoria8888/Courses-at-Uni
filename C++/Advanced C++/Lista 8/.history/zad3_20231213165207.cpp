#include <iostream>
#include <regex>

int main()
{

    std::regex rgx("^([[:upper:]][[:lower:]]*((-|[[:space:]])[[:upper:]][[:lower:]]*)*)$");

    std::string text;

    while (true)
    {
        std::cout << "Enter: ";
        std::getline(std::cin, text);
        if (text == "exit()")
        {
            break;
        }
        bool isMatch = std::regex_match(text, rgx);

        std::cout << "Is match: " << isMatch << std::endl;
    }
    return 0;
}
