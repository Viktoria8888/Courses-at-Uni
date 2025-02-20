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
const int N = 10000;
// The sum is always even.
// all even
// even number of odd
// 1 3 4
//  0 1 2 3 4 5 6 7 8 9 10
void solve(){
    int n;
    cin>>n;
    // cout<<n<<": ";
    if ((n/2)%2){
        cout<<"NO"<<endl;
        return;
    }
    else{
        ll sum = 0;
        vector<int> odd;
        vector<int> even;
        cout<<"YES"<<endl;

        for (int k = 2, i = 0; i < (n / 2); k += 2, i++) {
            sum+=k;
            even.push_back(k);
        }
        int curr = 0;
        for (int k = 1, i = 0; i < (n / 2) -1; k += 2, i++) {
            curr+=k;
            odd.push_back(k);
        }
        odd.push_back(sum-curr);
        rep(i,n/2){
            cout<<even[i]<<" ";
        }
         rep(i,n/2){
            cout<<odd[i]<<" ";
        }
        cout<<endl;

    }

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while (T--) {
        solve();
    }
    return 0;
}