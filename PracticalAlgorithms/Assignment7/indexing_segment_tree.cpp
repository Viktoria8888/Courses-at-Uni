#include "bits/stdc++.h"
using namespace std;
#include <cassert>
#define mod 1e9 + 7
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
const int MAXN = 200000;
// Segment Tree that implements finding the first element greater or equal the given value;
class SegmentTree{
private:
    int n;
    int s;
    vector<pair<int, ll>> T;
    // Builds the tree where each node corresponds to the size of the subtree;
    void Build(int ind, int l, int r, vector<ll>& arr){
        if (l > r) {
            return;
        }
        if (l==r) {
            T[ind] = {1,arr[l]};
            return;
        }
        int mid = l + (r - l) / 2;
        Build(ind*2,l,mid, arr);
        Build(ind*2+1,mid+1,r,arr);
        T[ind].first = T[ind*2].first +  T[ind*2+1].first;
    }
public:
    SegmentTree(vector<ll>& arr) : n(arr.size()), T(4 * n) {
        Build(1, 0, n-1, arr);
    }
    ll Delete(int v, int tl, int tr, int i){
        // cout<<tl<<" : "<<tr<<endl;
        if (tl > tr || i <= 0 || i > T[v].first) {
            return -1;
        }

        if (tl == tr) {
            T[v].first = 0;
            // cout<<tl<<": "<<T[v].second;
            return T[v].second;
        }
        int mid = tl + (tr-tl)/2;
        ll res;
        if (i>T[2*v].first) {
            res = Delete(2*v+1,mid+1,tr, i-T[2*v].first);

        }
        else {
            res = Delete(2*v,tl,mid, i);

        }
        T[v].first = T[2*v].first + T[2*v+1].first;
        return res;
    }

    ll GetIndex(int i) {
        ll res = Delete(1,0,n-1,i);
        return res;
    }





};

void test_all() {
    vector<ll> arr = {2,6,1,4,2};
    SegmentTree st(arr);
    ll res1 = st.GetIndex(3);

    // cout<<"result:"<<res1<<endl;
    assert(res1==1);
    ll res2 = st.GetIndex(1);
    assert(res2 == 2);

    ll res3 = st.GetIndex(3);
    assert(res3== 2);;

    // cout << "Test passed successfully!" << endl;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    test_all();


    int n, q;
    cin >> n;
    vector<ll> arr(n);
    rep(i,n) cin >> arr[i];
    SegmentTree tree(arr);
    rep(i,n){
        int val; cin>> val;
        cout << tree.GetIndex(val) << " ";
    }
    cout << endl;

    return 0;
}