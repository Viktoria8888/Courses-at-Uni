#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    vector<string> lines;

    cout << "Enter strings (Ctrl+D or Ctrl+Z to end input):\n";

    // Read strings until EOF is encountered
    copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(lines));

    // Print the entered strings
    cout << "Entered strings:\n";
    for (const auto& v : lines) {
        cout << v << endl;
    }

    return 0;
}
