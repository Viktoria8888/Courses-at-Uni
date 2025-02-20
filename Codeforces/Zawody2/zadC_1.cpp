#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#include <iostream>

int main() {
	int n, t;
	cin >> n >> t;
	string s1, s2;
	cin >> s1;
	cin >> s2;
	
	int good = 0;
	string res(n, ' ');
	int lastDiff = -1;

	char diffLetter = 'q';
	bool present[26] = {false};
	for (char ch : s1) {
		present[ch - 'a'] = true;

	}
	for (char ch : s2) {
		present[ch - 'a'] = true;

	}
	for (int i = 0; i < 26; i++) { 
		if (!present[i]) { 
			diffLetter = static_cast<char>(i + 'a'); 
			break;  
		}
	}

	for (int i = 0; i < n; i++) {
		if (good == n - t) {
			res[i] = diffLetter;
			//cout << "EEE" << endl;
			
		}
		else if (s1[i] != s2[i] ) {
			//cout << "I am here" << endl;
			if (lastDiff == -1) {
				lastDiff = i;
			}
			else {
				res[lastDiff] = s1[lastDiff];
				res[i] = s2[i];
				lastDiff = -1; // that index is already used
				good++;
			}
			
		}
		else {
			res[i] = s1[i];
			good++;
		}
	}
	//cout << good << endl;
	if (good == n - t) {
		cout << res << endl;
	}
	else {
		cout << -1 << endl;
	}

	return 0;
}