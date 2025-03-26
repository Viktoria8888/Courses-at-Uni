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
using vi = vector<int>;
void dfs(vector<vi>& adj, vi& count, int node){
    count[node]++;
    for (auto& v: adj[node]){
        dfs(adj,count,v);
        count[node]+=count[v];
    }
}
void solve(){
    int n;cin>>n;
    vector<vi> adj(n+1);
    vi count(n+1,0);
    repi(i,2, n+ 1){
        int a;cin>>a;
        adj[a].push_back(i);
    }
    dfs(adj,count,1);
    repi(i,1,n+1){
        cout<<count[i]-1<<" ";
    }
    cout<<endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}