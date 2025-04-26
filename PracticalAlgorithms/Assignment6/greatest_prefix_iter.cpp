#include "bits/stdc++.h"
using namespace std;
#define mod 1e9 + 7
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
#define F first
#define S second
#define PB push_back
#define INF 1000000000000000003
const int N = 200000;
using vi = vector<int>;

struct node {
    ll sum;
    ll pref;
    node() : sum(0), pref(0) {}
    node(ll sum, ll pref) : sum(sum), pref(max(0LL, pref)) {}
};

node T[4 * N];
int s;

void build() {
    for (int i = s - 1; i > 0; --i) {
        T[i].sum = T[i << 1].sum + T[i << 1 | 1].sum;
        T[i].pref = max(T[i << 1].pref, T[i << 1].sum + T[i << 1 | 1].pref);
    }
}

void modify(int ind, int value) {
    ind += s;
    T[ind] = node(value, value); 
    ind >>= 1;
    for (int i = ind; i >= 1; i >>= 1) {
        T[i].sum = T[i << 1].sum + T[i << 1 | 1].sum;
        T[i].pref = max(T[i << 1].pref, T[i << 1].sum + T[i << 1 | 1].pref);
    }
}

ll query(int l, int r) {
    node res(0, 0);
    l += s; r += s;
    while (l < r) {
        if (l & 1) {
            res.pref = max(res.pref, res.sum + T[l].pref);
            res.sum += T[l].sum;
            l++;
        }
        if (r & 1) {
            r--;
            res.pref = max(res.pref, res.sum + T[r].pref);
            res.sum += T[r].sum;
        }
        l >>= 1;
        r >>= 1;
    }
    return res.pref;
}

void solve() {
    int type;
    cin >> type;
    if (type == 1) {
        int y, v;
        cin >> y >> v;
        y--; 
        modify(y, v);
    } else {
        int x, y;
        cin >> x >> y;
        x--; y--;
        cout << query(x, y + 1) << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;

    for (s = 1; s < n; s <<= 1);

    rep(i, n) {
        int val;
        cin >> val;
        T[s + i] = node(val, val); 
    }

    build(); 

    rep(o, q) {
        solve(); 
    }

    return 0;
}
