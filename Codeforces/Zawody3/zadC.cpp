#include "bits/stdc++.h"
using namespace std;

#define mod 1000000007
#define rep(i, n) for (int i = 0; i < n; ++i)
typedef long long ll;
#define F first
#define S second
#define PB push_back
#define INF 1000000000000000003
const int N = 3000 + 7;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> A(n);
    int mini1 = 3001;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        mini1 = min(A[i], mini1);
    }

    int res = INT_MAX;

    for (int v = 1; v <= mini1; v++) {
        int maxi = 0, mini = INT_MAX;

        for (int i = 0; i < n; ++i) {
            int p_i = min(A[i] / v, k);
            // cout<<"v: "<<v<<" "<<"p_i: "<<p_i<<endl;
            if (p_i == 0) continue; 
            int value = A[i] / p_i;
            maxi = max(value, maxi);
            mini = min(value, mini);
        }

        if (mini != INT_MAX) { 
            res = min(res, maxi - mini);
        }
    }

    cout << res << endl;
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
