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
    int x1,x2,x3;
    cin>>x1>>x2>>x3;
    int dist = 0;
    int min_dist = INT_MAX;
    repi(a,1,11){
        dist = 0;
        dist = abs(a-x1)+ abs(a-x2) + abs(a-x3);
        min_dist = min(min_dist, dist);
    }
    cout<<min_dist<<endl;

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