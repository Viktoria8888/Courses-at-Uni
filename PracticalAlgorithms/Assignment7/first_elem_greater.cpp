#include "bits/stdc++.h"
using namespace std;
#include <cassert>
#define mod 1e9 + 7
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
const int MAXN = 200000;
// Segment Tree that implements finding the first element greater or equal the the given value;
class SegmentTree{
private:
    int n;
    int s;
    vector<pair<ll, int>> T;
    // Builds the max Segment Tree;
    void Build(int ind, int l, int r, vector<ll>& arr){
        if (l > r) {
            return;
        }
        if (l==r) {
            T[ind] = {arr[l],l};
            // arr[]
            // cout<<arr[l]<<": "<<l<<endl;
            return;
        }
        int mid = l + (r - l) / 2;
        Build(ind*2,l,mid, arr);
        Build(ind*2+1,mid+1,r,arr);
        T[ind].first = max(T[ind*2].first, T[ind*2+1].first);
    }
public:
    SegmentTree(vector<ll>& arr) : n(arr.size()), T(4 * n) {
        Build(1, 0, n-1, arr);
    }

    int GetS() const {
        return s;
    }


    void UpdateBy(int v, int tl, int tr, int i, int val){
        if (tl > tr) {
            return;
        }

        if (tl == tr) {
            T[v].first +=val;
            return;
        }

        int mid = tl + (tr-tl)/2;
        if (i <= mid) {
            UpdateBy(2*v, tl, mid, i, val);
        }
        else {
            UpdateBy(2*v+1, mid+1, tr, i, val);
        }
        T[v].first = max(T[2*v].first, T[2*v+1].first);
    }

    // returns the index of the first element in the array that is greater or equal than val
    // if such value doesn't exist returns -1
    // int QueryMax(int v, int tl, int tr, int l, int r){
    //     if (l > r || l > tr || r < tl) {
    //         return INT_MIN;
    //     }
    //
    //     if (l <= tl && tr <= r) {
    //         return T[v];
    //     }
    //
    //     int mid = tl + (tr-tl)/2;
    //     return max(QueryMax(2*v, tl, mid, l, r),
    //               QueryMax(2*v+1, mid+1, tr, l, r));
    // }
    int QueryGreatest(int v, int tl, int tr, int val){
        // if (l > r || l > tr || r < tl) {
        //     return INT_MIN;
        // }
        if (T[v].first < val) {
            return 0;
        }

        if (tr==tl) {
            int index = T[v].second;
            Update(index,-val);
            return index + 1;
        }

        int mid = tl + (tr-tl)/2;
        if (T[2*v].first < val) {
            return QueryGreatest(2*v+1, mid + 1, tr, val);
        }
        else {
            return QueryGreatest(2*v, tl, mid, val);
        }

    }


    void Update(int i, int val) {
        UpdateBy(1, 0, n-1, i, val);
    }

    int Query(int val) {
        return QueryGreatest(1, 0, n-1, val);
    }

};

void test_all() {
    vector<ll> arr = {3, 2, 4, 1, 5, 5, 2, 6};
    SegmentTree st(arr);


    // st.Update(1, 0, 9, 0, 100);
    // assert(st.QueryMax(1, 0, 9, 0, 0) == 100);
    //
    //
    // assert(st.QueryMax(1, 0, 9, 0, 5) == 100);
    // assert(st.QueryMax(1, 0, 9, 1, 5) == 6);

    assert(st.Query(4) == 3);
    assert(st.Query(4) == 5);
    assert(st.Query(4) == 6);
    // cout << "Test passed successfully!" << endl;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // test_all();


    int n, q;
    cin >> n >> q;
    vector<ll> arr(n);
    rep(i,n) cin >> arr[i];
    SegmentTree tree(arr);
    while (q--) {
        int val; cin>> val;
        cout << tree.Query(val) << " ";
    }
    cout << endl;

    return 0;
}