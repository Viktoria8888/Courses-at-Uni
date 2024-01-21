#include <iostream>
#include <regex>
using namespace std;

int main()
{
    std::regex rgx("\\((-?\\d*\\.?\\d+)[+-](\\d*\\.?\\d*)[iI]\\)");
    while (true)
    {
        string expr;
        getline(cin, expr);
        if (expr == "exit()")
        {
            break;
        }
        bool is_match = regex_match(expr, rgx);
        cout << is_match << endl;
    }

    return 0;
}
