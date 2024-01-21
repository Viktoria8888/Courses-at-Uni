#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    vector<string> lines;
    auto it = back_inserter(lines);
    *it = "wtf";

    // copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(lines));

    cout << "Entered strings:\n";
    for (const auto& v : lines) {
        cout << v << endl;
    }

    return 0;
}
