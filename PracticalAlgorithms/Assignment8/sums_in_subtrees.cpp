#include "bits/stdc++.h"
using namespace std;
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
#define F first
#define S second
#define PB push_back
const int N = 200000 + 3;
using vi = vector<int>;
bool TEST = true;
ll values[N];
vi adj[N];
class EulerTour {
private:
    int n;
    int TIME = 1;
public:
    vector<ll> tour;
    vector<int> start;
    vector<int> end;
    EulerTour(const int _n, const vector<int>& parents): n(_n), start(_n+1, -1), end(_n+1,-1){
        tour.push_back(0);
        dfs(1,-1);
    }
    void dfs(int node, int p) {
        tour.push_back(values[node]);
        start[node] = tour.size() - 1;
        for (const auto& neigh: adj[node]) {
            if (neigh != p) {
                dfs(neigh, node);
            }
        }
        tour.push_back(0);
        end[node] = tour.size() - 1;
    }
};


class SegmentTree {
private:
    vector<ll> T;
    vector<ll> arr;
    int n;
    void build(int v, int tl, int tr) {
        if (tl > tr) {
            return;
        }
        if (tl==tr) {
            T[v] = arr[tr];
            return;
        }
        int mid = tl + (tr-tl)/2;
        build(v<<1, tl,mid);
        build((v<<1)|1, mid+1,tr);
        T[v] = T[v<<1] + T[(v<<1)|1];
    }
    ll find_sum(int v, int tl, int tr, int l, int r) {
        if (tl > tr || l > r) {
            return 0;
        }
        if (tl == l && tr == r) {
            return T[v];
        }
        int mid = tl + (tr-tl)/2;
        // 1) just left interval: l<r<=mid
        return find_sum(v<<1,tl,mid, l, min(mid, r)) + find_sum((v<<1)|1,mid+1,tr, max(l,mid+1), r) ;
    }
    void modify(int v,int tl,int tr, int i, ll k) {
        if (tl > tr) {
            return;
        }
        if (tl==tr) {
            T[v] = k;
            return;
        }
        int mid = tl + (tr-tl)/2;
        if (i <= mid) {
            modify(v<<1, tl,mid,i,k);

        }
        else {
            modify((v<<1)|1, mid+1,tr,i,k);
        }
        T[v] = T[v<<1] + T[(v<<1)|1];
    }
public:
    SegmentTree(int _n,vector<ll>& _arr):n(_n), arr(_arr), T(4*_arr.size(),0) {
        build(1,1,n);
    }
    ll find_sum(int l, int r) {
        return find_sum(1,1,n,l,r);
    }
    void modify(int i, ll k) {
        modify(1,1,n,i,k);
    }

};
void test_stree() {
    vector<ll> arr = {0,1,2,3,4,5};
    SegmentTree st(5,arr);
    assert(st.find_sum(1,5)==15);
    st.modify(5,0);
    assert(st.find_sum(1,5)==10);
}
void solve(int n, int q, vector<int>& parent){
    EulerTour e(n,parent);
    ll arr;
    SegmentTree st(e.tour.size(), e.tour);
    rep(i,q) {
        int t; cin>>t;
        if (t==1) {
            int v,x;cin>>v>>x;
            st.modify(e.start[v], x);
        }
        else {
            int v; cin>>v;
            cout<<st.find_sum(e.start[v],e.end[v])<<'\n';

        }
    }
}

void build_parent(int node, int p, vi& parent) {
    parent[node] = p;
    for (int neigh : adj[node]) {
        if (neigh != p) {
            build_parent(neigh, node, parent);
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(nullptr);
    // test_stree();
    int n,q; cin>>n>>q;
    vi parent(n+1,-1);
    rep(i,n) {
        cin>>values[i+1];
    }
    rep(i,n-1){
        int v,u;cin>>v>>u;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }
    build_parent(1,-1,parent);
    solve(n,q,parent);
    return 0;
}