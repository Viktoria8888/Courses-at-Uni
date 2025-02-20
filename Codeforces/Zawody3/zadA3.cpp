#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main(){


	int t; cin >> t;
	for (int i = 0; i < t; i++) {
		unordered_set<char> seen;
		string st; cin >> st;
		int days = 0;
        for (auto ch : st) {
            if (seen.size() == 3 && seen.find(ch) == seen.end()) {
                days++;
                seen.clear();
            }
            seen.insert(ch);
        }

        if (!seen.empty()) {
            days++;
        }

        cout << days << endl;
	}
	
	return 0;
};