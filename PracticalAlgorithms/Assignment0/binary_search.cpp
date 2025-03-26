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
const int N = 100000;
using vi = vector<int>;
int arr[N];
int n;

void solve(int x){
    int l = 0, r = n-1;
    while (l <= r){
        int mid = (r-l)/2 + l;
        if (arr[mid] == x){
            cout<<mid+1<<endl;
            return;
        }
        else if (arr[mid] < x){
            l = mid+1;
         
        }
        else{
            r = mid - 1;
        }
    }
    cout<<-1<<endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    rep(i,n){
        cin>>arr[i];
    }
    int m; cin>>m;
    rep(i,m){
        int x;cin>>x;
        solve(x);
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

// The original last_true function
int last_true(int lo, int hi, function<bool(int)> f) {
    // if none of the values in the range work, return lo - 1
    lo--;
    while (lo < hi) {
        // find the middle of the current range (rounding up)
        int mid = lo + (hi - lo + 1) / 2;
        if (f(mid)) {
            // if mid works, then all numbers smaller than mid also work
            lo = mid;
        } else {
            // if mid does not work, greater values would not work either
            hi = mid - 1;
        }
    }
    return lo;
}

// Function to check if element exists in sorted array
bool elementExists(vector<int>& arr, int target) {
    if (arr.empty()) return false;
    
    int n = arr.size();
    
    // Define our predicate function 
    // We want to find the last index where arr[i] <= target
    auto predicate = [&](int i) {
        return arr[i] <= target;
    };
    
    // Run binary search
    int pos = last_true(0, n-1, predicate);
    
    // Check if we found a valid position and if the element at that position equals target
    return (pos >= 0 && pos < n && arr[pos] == target);
}

int main() {
    // Example usage
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    
    cout << "Testing element existence:" << endl;
    
    // Test cases
    cout << "Is 7 in the array? " << (elementExists(arr, 7) ? "Yes" : "No") << endl;
    cout << "Is 8 in the array? " << (elementExists(arr, 8) ? "Yes" : "No") << endl;
    cout << "Is 1 in the array? " << (elementExists(arr, 1) ? "Yes" : "No") << endl;
    cout << "Is 15 in the array? " << (elementExists(arr, 15) ? "Yes" : "No") << endl;
    cout << "Is 0 in the array? " << (elementExists(arr, 0) ? "Yes" : "No") << endl;
    cout << "Is 16 in the array? " << (elementExists(arr, 16) ? "Yes" : "No") << endl;
    
    return 0;
}