#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Remove duplicates and sort to get unique increasing sequence
    set<int> unique_elements(a.begin(), a.end());
    cout << unique_elements.size() << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
