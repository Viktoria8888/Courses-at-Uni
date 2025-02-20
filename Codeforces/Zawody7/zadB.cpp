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

const int N = 100000+7;
ll a[N];
ll b[N];

bool canBakeM(ll n, ll k, ll m){
    ll magic_needed = 0;
    for (int i = 0 ; i< n; ++i){
        ll needed_ing =     a[i]*m;
        if (needed_ing > b[i]){
            magic_needed += needed_ing - b[i];
        }   
        if (magic_needed > k){
            return false;
        }
    }
    return true;

}
        
ll last_true(ll n, ll k, ll lo, ll hi) {

	// if none of the values in the range work, return lo - 1

	lo--;

	while (lo < hi) {

		// find the middle of the current range (rounding up)

		int mid = lo + (hi - lo + 1) / 2;

		if (canBakeM(n,k,mid)) {
            cout<<"mid: "<<mid<<endl;

			// if mid works, then all numbers smaller than mid also work

			lo = mid;

		} else {

			// if mid does not work, greater values would not work either

			hi = mid - 1;

		}

	}

	return lo;

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k; cin>>n>>k;
    ll mini = LLONG_MAX; // Use a sufficiently large value for comparison

    rep(i,n){
        cin>>a[i];
    }
    rep(i,n){
        ll c; cin>>c;
        b[i] = c;
        mini = min(1LL * (b[i] / a[i]), mini);
    }
    int res = mini;
    int i = mini + 1;
    
    cout<<last_true(n,k,i,2*1000000000+7);

    return 0;
}