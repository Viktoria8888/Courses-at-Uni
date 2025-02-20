#include "bits/stdc++.h"
using namespace std;

#define rep(i, n) for (int i = 0; i < n; ++i)
typedef long long ll;

const int N = 100 + 7;
char A[N][N];

void solve() {
    int r, c, k;
    cin >> r >> c >> k;

    vector<string> farm(r);
    int rice = 0;
    rep(i, r) {
        cin >> farm[i];
        rep(j, c) if (farm[i][j] == 'R') rice++;
    }

    int equal = rice / k, mod = rice % k;
    string names = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int chicken_id = 0, curr_count = (mod > 0) ? (equal + 1) : equal;
    mod--;
    bool reverse_row = false;

    rep(i, r) {
        rep(t, c) {
            int j = reverse_row ? (c - t - 1) : t;
            A[i][j] = names[chicken_id];
            if (farm[i][j] == 'R') curr_count--;
            if (curr_count == 0 && chicken_id + 1 < k) {
                chicken_id++;
                curr_count = (mod > 0) ? (equal + 1) : equal;
                mod--;
            }
        }
        reverse_row = !reverse_row;
    }

    rep(i, r) {
        rep(j, c) c out << A[i][j];
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
