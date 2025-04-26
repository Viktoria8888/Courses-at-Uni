#include "bits/stdc++.h"
using namespace std;
#define mod 1e9 + 7
#define rep(i, n) for (int i = 0; i < n; ++i)
#define repi(i, s, n) for (int i = s; i < n; ++i)
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

ll a[N];
node tt[4 * N];
int n, q;

node merge(const node &a, const node &b) {
    return {a.sum + b.sum, max(a.pref, a.sum + b.pref)};
}

void build(int k = 1, int l = 1, int r = n) {
    if (l == r) {
        tt[k] = node(a[l], a[l]); 
        return;
    }
    int m = (l + r) >> 1;
    build(k << 1, l, m);
    build(k << 1 | 1, m + 1, r);
    tt[k] = merge(tt[k << 1], tt[k << 1 | 1]);
}

void modify(int i, int x, int k = 1, int l = 1, int r = n) {
    if (l == r) {
        tt[k] = node(x, x); 
        return;
    }
    int m = (l + r) >> 1;
    if (i <= m)
        modify(i, x, k << 1, l, m);
    else
        modify(i, x, k << 1 | 1, m + 1, r);
    tt[k] = merge(tt[k << 1], tt[k << 1 | 1]);
}

node query(int ql, int qr, int k = 1, int l = 1, int r = n) {
    if (ql > r || qr < l) return node(0, 0); 
    if (ql <= l && qr >= r) return tt[k];
    int m = (l + r) >> 1;
    node q1 = query(ql, qr, k << 1, l, m);
    node q2 = query(ql, qr, k << 1 | 1, m + 1, r);
    return merge(q1, q2);
}

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build();
    for (int i = 0, t, x, y; i < q; ++i) {
        cin >> t >> x >> y;
        if (t == 1)
            modify(x, a[x] = y);
        else
            cout << query(x, y).pref << "\n";
    }
    return 0;
}