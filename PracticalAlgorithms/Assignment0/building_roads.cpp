#include "bits/stdc++.h"
using namespace std;
#define mod 1e9 + 7
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
const int N = 100000 + 5;
int vis[N];
void dfs(vector<vector<int>>& g, int node){
    vis[node] = 1;

    for (auto& neigh: g[node]){
        if (!vis[neigh]){
            dfs(g,neigh);
        }
    }

}
void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> g(n+1);
    rep(i,m){
        int a,b;
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int count = 0;
    repi(i,1,n+1){
        if (!vis[i]){
            count++;
            dfs(g,i);
        }
    }
    cout<<count-1<<endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}