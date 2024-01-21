#include <iostream>
#include <regex>
using namespace std;

int main() {
    std::regex rgx("\\(([+-]?\\d*\\.?\\d+)[+-]?(\\d*\\.?\\d+)(i|I)\\)");
                   //"\\(([+-]?\\d*\\.?\\d+)[+-]?(\\d*\\.?\\d*)i\\)"
    bool is_match = regex_match("(7.4+0.5i)",rgx);
    cout<<is_match<<endl;
    return 0;
}
