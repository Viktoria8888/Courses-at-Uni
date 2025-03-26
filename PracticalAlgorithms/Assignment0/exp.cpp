#include "bits/stdc++.h"
using namespace std;
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
#define F first
#define S second
#define PB push_back
#define INF 1000000000000000003
const int N = 10000;
using vi = vector<int>;
const ll mod = 1e9 ;

ll exp_it(ll a, ll n) {
    ll result = 1;
    
    while (n > 0) {
        if (n & 1) {
            result = (result* a) % mod;
        }
        
        a = (a * a) % mod;
        n/=2;
    }
    
    return result;
}
void solve(){    
    ll a,n; cin>>a>>n;
    cout<<exp_it(a,n)<<endl;

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}