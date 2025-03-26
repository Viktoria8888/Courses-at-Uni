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
using vi = vector<int>;
ll a[N];
ll p[N];

ll gcd(ll& k, ll& l, ll a, ll b){
    if (b == 0){
        k = 1;
        l = 0;
        return a;
    }
    ll k_prev, l_prev;
    ll d = gcd(k_prev,l_prev,b,a%b);
    k = l_prev;
    l = k_prev - (l_prev* (a/b));
    return d;
    
}

void solve(){
    int k;cin>>k;
    ll m = 1;
    rep(i,k){
        cin>>p[i]>>a[i];
        m*=p[i];
    }
    ll A = 0;
    rep(i,k){
        ll k,l;
        int d = gcd(k,l,m/p[i],p[i]);
        A += a[i]*(m/p[i])*k;
    }
    cout<<((A % m) + m)%m<<endl;

}
//O(N*K*log(p^K)) = O(N*K^2*log(max(p)))

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