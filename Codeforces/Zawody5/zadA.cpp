#include <iostream>
#include <vector>

using namespace std;

int main() {

	string s;
	cin >> s;
	
	for (int i = 1; i < s.size(); i++) {
		if (s[i] == s[i - 1]) {
			for (char c = 'a'; c <= 'z'; c++) {
				if (c != s[i] && (i + 1 >= s.size() || s[i + 1] != c)) {
					s[i] = c;
					break;
				}
			}
		}
	}

	cout << s << endl;
	return 0;
}