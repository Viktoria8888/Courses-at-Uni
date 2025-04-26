#include "bits/stdc++.h"
#include <cassert>
using namespace std;
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
constexpr int N = 60000;

struct node {
    int min;
    int change;
    node():min(0), change(0){}
    node(int _min, int _change): min(_min),change(_change) {}
};
// Node: 4 bytes + 4 bytes = 8 bytes;
// Size of T = 4 * 60000 = 240000;
//

node T[4*N]; // 8 bytes * 240000 = 4bytes * 200000 = 1,920,000 bytes = 1.83 MB;

int n, m;

void build(int v, int tl, int tr) {
    if (tl > tr) {
        return;
    }
    if (tl==tr) {
        T[v] = node(m,0);
        return;
    }
    int mid = tl + (tr - tl)/2;
    build(2*v, tl,mid);
    build(2*v+1, mid+1, tr);
    T[v].min = min(T[2*v].min, T[2*v+1].min);
}

int find_min(int v, int tl, int tr, int l, int r, int change) {
    if (tl > tr || l > r) {
        return INT_MAX;
    }
    if (tl==l && tr == r) {
        // cout<<tl<<" : "<<tr<<endl;
        return T[v].min + change;
    }
    int mid = tl + (tr-tl) / 2;
    return min(
        find_min(2*v, tl, mid, l, min(r, mid), change + T[v].change),
        find_min(2*v+1, mid+1, tr, max(l, mid+1), r, change + T[v].change)
    );

}
void update(int v, int tl, int tr, int l, int r, int val, int change=0) {
    if (tl > tr || l > r) {
        return;
    }
    if (tl == l && tr == r) {
        T[v].min = T[v].min + val;
        T[v].change += val;
        return;
    }
    int mid = tl + (tr - tl)/2;
    update(2*v, tl, mid, l, min(r, mid), val, change + T[v].change);
    update(2*v+1, mid+1, tr, max(l, mid+1), r, val, change + T[v].change);
    T[v].min = min(T[2*v].min, T[2*v+1].min) + T[v].change;

}
void test_all() {
    n = 4;
    m = 6;
    build(1,0,n-1);
    assert(find_min(1,0,n-1,0,3,2) >= 4);
    // update(1,0,n-1,0,3,1);
    // assert(find_min(1,0,n-1,0,1,0) == 5);
    // update(1,0,n-1,0,1,1);
    // assert(find_min(1,0,n-1,0,1,0) == 4);

}

void solve(){
    int p,k,l;cin>>p>>k>>l;
    // p--;k--;
    int res = find_min(1,1,n-1,p,k-1,0);
    // cout<<res<<endl;
    if (res < l) {
        cout<<"N"<<endl;
    }
    else {
        cout<<"T"<<endl;
        update(1,1,n-1,p,k-1,-l);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // test_all();
    int q; cin>>n>>m>>q;
    // rep(i,n){arr[i]=m;}
    build(1,1,n-1);
    while (q--) {
        solve();
    }

    return 0;
}