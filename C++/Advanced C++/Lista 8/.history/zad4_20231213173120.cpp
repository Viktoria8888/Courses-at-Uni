#include <iostream>
#include <regex>
using namespace std;

int main()
{
    std::regex rgx("\\(([+-]?\\d+\\.?\\d+)[+-]?(\\d+\\.?\\d+)(i|I)\\)");
    //"\\(([+-]?\\d*\\.?\\d+)[+-]?(\\d*\\.?\\d*)i\\)"

    while (true)
    {
    std:
        cout << "Enter: ";
        std::string expr;
        std::getline(std::cin, expr);
        if (expr== "exit()"){
            break;
        }
        bool is_match = regex_match(expr, rgx);
        cout << "Is match: "<<is_match << endl;
    }
    return 0;
}
