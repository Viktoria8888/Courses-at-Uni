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
const int N = 2*100000;
int count[N]; // count[i]: the number of nodes on a path not including ith node
int vis[N];
// void dfs(vector<vector<int>)

void solve(){
    int n;
    cin>>n;
    vector<int> g;
    rep(i,n){
        int a;cin>>a;
        g.push_back(a);
    }
    ll res = 1;
    rep(i,n){
        if (vis[g[i]]){

        }
        if (i>0){
            count[i-1]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve()
    return 0;
}