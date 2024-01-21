#include <iostream>
#include <regex>
using namespace std;

int main() {
    std::regex rgx("\\((-?\\d*\\.?\\d+)[+-](\\d*\\.?\\d*)[iI]\\)");

    bool is_match = regex_match("(73.12+5I)", rgx);
    cout << is_match << endl;

    return 0;
}
