#include <iostream>
#include <regex>
using namespace std;

int main() {
    std::regex rgx("^(\(\\d+\\d\))$");
    bool is_match = regex_match("(3+2)",rgx);
    cout<<is_match<<endl;
    return 0;
}
