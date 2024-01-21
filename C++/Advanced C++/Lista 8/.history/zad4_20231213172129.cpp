#include <iostream>
#include <regex>
using namespace std;

int main() {
    std::regex rgx("\\(([+-]?\\d+\\.?\\d+)[+-]?(\\d+\\.?\\d+)i|I\\)");
    bool is_match = regex_match("(3+2i)",rgx);
    cout<<is_match<<endl;
    return 0;
}
