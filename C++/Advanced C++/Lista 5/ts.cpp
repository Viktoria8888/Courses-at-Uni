#include <string>
#include <forward_list>
#include <iostream>

int main() {
    std::string s = "abcd";
    std::forward_list<char> res;
    std::forward_list<char> res2;

    auto before_end = res.before_begin();
    for (auto &_ : res)
        ++before_end;

    for (auto &e : s) {
        res.insert_after(before_end, e);
        before_end++;
    }

    for (auto &e : s) {
        res2.push_front(e);
    }

    for (auto &element : res) {
        std::cout << element;
    }
    std::cout << '\n';

    for (auto &element : res2) {
        std::cout << element;
    }
    std::cout << '\n';
}
