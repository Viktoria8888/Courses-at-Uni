#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

int main()
{
    vector<string> lines;
    std::copy(
        istream_iterator<std::string>(cin),
        istream_iterator<std::string>(),
        back_inserter(lines));
    for (const auto& v: lines){
        cout<<v<<endl;
    }
    return 0;
}
