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
    string a,b,c;
    cin>>a>>b;
    c = b+b;
    int n = a.size(), m = b.size();
    int count = 0;
    rep(i,n-m+1){
        bool same = true;
        rep(j,m){
            if (a[i+j]!=b[j]){
                same = false;
            }
        }
        if (same){
            a[i+m-1] = '#';
            count++;
        }
    }
    // cout<<a<<endl;
    cout<<count<<endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
