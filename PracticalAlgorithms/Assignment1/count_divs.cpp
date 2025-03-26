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
const int N = 1000000;
int d[N];
using vi = vector<int>;

void solve(){
    int x;cin>>x;
    cout<<d[x]<<endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    repi(i,1,N+1){
        for (int j = i; j <= N; j+=i){
            d[j]++;
        }
    }
    int T;
    cin>>T;
    while (T--) {
        solve();
    }
    return 0;
}