#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

struct node {
    ll sum;
    bool marked;
    ll lazy;
    node(): sum(0), marked(false), lazy(0) {}
    node(ll val): sum(val), marked(false), lazy(0){}
};

class SegmentTree {
    int n;
    vector<node> T;

    void build(int v, int tl, int tr, vector<ll>& arr) {
        if (tl == tr) {
            T[v] = node(arr[tl]);
            return;
        }
        int mid = (tl + tr) / 2;
        build(2*v, tl, mid, arr);
        build(2*v+1, mid+1, tr, arr);
        T[v].sum = T[2*v].sum + T[2*v+1].sum;
    }

    void push(int v, int tl, int tr) {
        if (T[v].marked) {
            apply(2*v, tl, (tl + tr) / 2, T[v].lazy);
            apply(2*v+1, (tl + tr) / 2 + 1, tr, T[v].lazy);
            T[v].marked = false;
            T[v].lazy = 0;
        } else if (T[v].lazy != 0) {
            int mid = (tl + tr) / 2;
            T[2*v].lazy += T[v].lazy;
            T[2*v+1].lazy += T[v].lazy;
            T[2*v].sum += T[v].lazy * (mid - tl + 1);
            T[2*v+1].sum += T[v].lazy * (tr - mid);
            T[v].lazy = 0;
        }
    }

    void apply(int v, int tl, int tr, ll val) {
        T[v].sum = val * (tr - tl + 1);
        T[v].lazy = val;
        T[v].marked = true;
    }

    void set_value(int v, int tl, int tr, int l, int r, ll val) {
        if (l > r) return;
        if (tl == l && tr == r) {
            apply(v, tl, tr, val);
            return;
        }
        push(v, tl, tr);
        int mid = (tl + tr) / 2;
        set_value(2*v, tl, mid, l, min(r, mid), val);
        set_value(2*v+1, mid+1, tr, max(l, mid+1), r, val);
        T[v].sum = T[2*v].sum + T[2*v+1].sum;
    }

    ll query_sum(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (tl == l && tr == r) return T[v].sum;
        push(v, tl, tr);
        int mid = (tl + tr) / 2;
        return query_sum(2*v, tl, mid, l, min(r, mid)) +
               query_sum(2*v+1, mid+1, tr, max(l, mid+1), r);
    }

    void update_by(int v, int tl, int tr, int l, int r, ll val) {
        if (l > r) return;
        if (tl == l && tr == r) {
            if (T[v].marked) {
                apply(v, tl, tr, T[v].lazy + val);
            } else {
                T[v].lazy += val;
                T[v].sum += val * (tr - tl + 1);
            }
            return;
        }
        push(v, tl, tr);
        int mid = (tl + tr) / 2;
        update_by(2*v, tl, mid, l, min(r, mid), val);
        update_by(2*v+1, mid+1, tr, max(l, mid+1), r, val);
        T[v].sum = T[2*v].sum + T[2*v+1].sum;
    }

public:
    SegmentTree(vector<ll>& arr) : n(arr.size()), T(4 * n) {
        build(1, 0, n-1, arr);
    }

    void set(int l, int r, ll val) {
        set_value(1, 0, n-1, l-1, r-1, val);
    }

    ll query(int l, int r) {
        return query_sum(1, 0, n-1, l-1, r-1);
    }

    void update(int l, int r, ll val) {
        update_by(1, 0, n-1, l-1, r-1, val);
    }
};

void solve(vector<ll>& arr, SegmentTree& st) {
    int k, x, y;
    cin >> k >> x >> y;
    if (k == 1) {
        ll v; cin >> v;
        st.update(x, y, v);
    } else if (k == 2) {
        ll v; cin >> v;
        st.set(x, y, v);
    } else {
        cout << st.query(x, y) << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<ll> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];
    SegmentTree st(arr);
    for (int i = 0; i < q; ++i) {
        solve(arr, st);
    }
    return 0;
}
