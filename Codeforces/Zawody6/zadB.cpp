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



int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while (T--) {
        int n,m;
    cin>>n>>m;

    int s = 0;
    rep(i,n){int a;cin>>a;s+=a;}
    if (m !=n  || n ==2) {cout<<-1<<endl;continue;}
    cout<<s*2<<endl;
    rep(i,m-1){
        cout<<i+1<<" "<<i+2<<endl;
    }
    cout<<m<<" "<<1<<endl;
    }
    return 0;
}