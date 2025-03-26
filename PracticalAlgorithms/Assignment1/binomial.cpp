#include "bits/stdc++.h"
using namespace std;
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
#define F first
#define S second
#define PB push_back
#define INF 1000000000000000003
const int N = 1000000;
using vi = vector<int>;
ll const mod = 1e9 + 7;
ll fact[N];
ll inv[N];
ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll gcd = extended_gcd(b, a % b, x1, y1);
    
    x = y1;
    y = x1 - ((a / b) * y1) % mod;
    
    return gcd;
}
void solve(){
    ll a,b;cin>>a>>b;
    ll x,y;
    ll b1 = (fact[b] * fact[a-b]) % mod;

    extended_gcd(b1,mod,x,y);
    ll res = (fact[a] * (x % mod + mod) % mod) % mod;

    cout<<res<<endl;

    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fact[0] = 1;
    repi(i,1,N+1){
        fact[i] = (fact[i-1]*i) % mod;
    }
    int T;
    cin>>T;
    while (T--) {
        // cout<<"T:";
        solve();
        
    }
    return 0;
}