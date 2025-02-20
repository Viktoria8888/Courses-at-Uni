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
    int m,n;cin>>m>>n;
    double res = 0.0;
    rep(i,m) { // Outer loop
    double prob_leq = pow((i + 1) / (double)m, n);  // (i+1)/m for P(X <= i)
    double prob_less = pow(i / (double)m, n);       // i/m for P(X < i)
    res += (i + 1) * (prob_leq - prob_less);        // i+1 is the value of X
}

    cout<<res<<endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}