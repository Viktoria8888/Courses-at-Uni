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

void solve(){
    ll n;
    cin>>n;
    ll bug = (n + 4) / 1 * (n + 3) / 2 * (n + 2) / 3 * (n + 1) / 4 * n / 5;
    ll feature = (n + 2) / 1 * (n + 1) / 2 * n / 3;
    ll res =  bug* feature;
    cout<<res<<endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    solve();
    return 0;
}