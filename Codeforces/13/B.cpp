#include "bits/stdc++.h"
using namespace std;

#define mod 1000000007
#define rep(i, n) for (int i = 0; i < n; ++i)
#define repi(i, s, n) for (int i = s; i < n; ++i)
typedef long long ll;
#define F first
#define S second
#define PB push_back
#define INF 1000000000000000003
const int N = 10000;

void solve() {
    ll xa, ya, xb, yb, xc, yc;
    cin >> xa >> ya;
    cin >> xb >> yb;
    cin >> xc >> yc;

    ll AB[2] = {xb-xa, yb - ya};
    ll BC[2] = {xc - xb, yc - yb};

    
    ll cross_product = AB[0] * BC[1] - AB[1] * BC[0];
    if (cross_product > 0) {
        cout << "LEFT" << endl;
    } else if (cross_product < 0) {
        cout << "RIGHT" << endl;
    } else {
        cout << "TOWARDS" << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
