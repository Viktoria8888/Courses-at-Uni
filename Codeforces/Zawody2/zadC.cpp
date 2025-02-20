#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#include <iostream>

int main() {
	ios::sync_with_stdio(0);
    cin.tie(0);
	int n, t;
	cin >> n >> t;
	string s1, s2;
	cin >> s1;
	cin >> s2;

	string res(n, '?');
	int good1 = n - t, good2 = n - t;

	for (int i = 0; i < n; i++) {
		if (good1 == 0) {
			break;
		}
		if (s1[i] == s2[i]) {
			res[i] = s1[i];
			good1--;
			good2--;
		}
	}
	// if there are some unmatched letters left for first word
	for (int i = 0; i < n && good1 > 0; i++) {
		if (res[i] == '?') {
			res[i] = s1[i];
			good1--;
		}
	}
	// if there are some unmatched letters left for second word
	for (int i = 0; i < n && good2 > 0; i++) {
		if (res[i] == '?') {
			res[i] = s2[i];
			good2--;
		}
	}
	// fill in the rest
	for (int i = 0; i < n; i++) {
		if (res[i] == '?') {
			for (int j = 'a'; j <= 'z'; j++)
			{
				if (s1[i] != j && s2[i] != j)
				{
					res[i] = j; break;
				}
			}
		}
	}
	int t1 = 0, t2 = 0;

	for (int i = 0; i < n; i++)
	{
		if (res[i] != s1[i])
			t1++;

		if (res[i] != s2[i])
			t2++;
	}

	if (t == t1 && t == t2)
		cout << res;

	else
		cout << "-1";

}