#include <iostream>
#include <unordered_set>
#include <string>
typedef std::unordered_set<std::string> MyStringSet;
int main() {
    MyStringSet strings= {"Haskell", "Ruby", "Python", "JavaScript", "TypeScript"};
    for (const auto& s: strings){
        std::cout<<s<<std::endl;
    }
    return 0;
}
