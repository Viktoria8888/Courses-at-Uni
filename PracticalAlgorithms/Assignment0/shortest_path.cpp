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
const int N = 100000 + 5;

void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> adj(n+1);
    rep(i,m){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    queue<int> q;
    q.push(1);
    vector<int> dist(n+1, INT_MAX);
    dist[1] = 0;
    while (!q.empty()){
        int curr = q.front();
     
        q.pop();
        for (auto& neigh: adj[curr]){
            if (dist[neigh]==INT_MAX){
                q.push(neigh);
                dist[neigh] = dist[curr] + 1;}
        }
    }
    repi(i,2,n+1){
        if (dist[i] == INT_MAX){
            cout<<-1<<" ";
        }
        else{
        cout<<dist[i]<<" ";}
    }
    cout<<endl;

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}