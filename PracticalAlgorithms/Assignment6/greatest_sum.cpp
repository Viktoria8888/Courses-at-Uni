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
	ll suf;
	ll maxi;
	node() : sum(0), pref(0), suf(0), maxi(0) {} 
    node(int l) : sum(l), pref(l), suf(l), maxi(l){}
    node(ll sum, ll pref, ll suf, ll maxi) : sum(sum), pref(pref), suf(suf), maxi(maxi){}
};

ll a[N];
node tt[4 * N];
int n, q;

node merge(const node &a, const node &b) {
	return node(
        a.sum + b.sum,                          
        max(a.pref, a.sum + b.pref),            
        max(b.suf, b.sum + a.suf),              
        max(max(a.maxi, b.maxi), a.suf + b.pref) 
    );
}

void build(int k = 1, int l = 1, int r = n) {
    if (l == r) {
        tt[k] = node(a[l]); 
        return;
    }
    int m = (l + r) >> 1;
    build(k << 1, l, m);
    build(k << 1 | 1, m + 1, r);
    tt[k] = merge(tt[k << 1], tt[k << 1 | 1]);
}

void modify(int i, int x, int k = 1, int l = 1, int r = n) {
    if (l == r) {
        tt[k] = node(x); 
        return;
    }
    int m = (l + r) >> 1;
    if (i <= m)
        modify(i, x, k << 1, l, m);
    else
        modify(i, x, k << 1 | 1, m + 1, r);
    tt[k] = merge(tt[k << 1], tt[k << 1 | 1]);
}

// node query(int ql, int qr, int k = 1, int l = 1, int r = n) {
//     if (ql > r || qr < l) return node(0); 
//     if (ql <= l && qr >= r) return tt[k];
//     int m = (l + r) >> 1;
//     node q1 = query(ql, qr, k << 1, l, m);
//     node q2 = query(ql, qr, k << 1 | 1, m + 1, r);
//     return merge(q1, q2);
// }

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build();
    for (int i = 0, x, y; i < q; ++i) {
        cin >> x >> y;
		modify(x, a[x] = y);
		cout << max(0LL, tt[1].maxi) << "\n";
    }
    return 0;
}