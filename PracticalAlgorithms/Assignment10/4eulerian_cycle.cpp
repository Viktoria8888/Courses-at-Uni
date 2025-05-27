#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
const int N = 100000 + 1;
const int M = 200000 + 1;
vector<pair<int,int>> adj[N];
int deleted_edges[M];
int in_deg[N];
int out_deg[N];
int vis[N];
void dfs(int v, vector<int>& res)
{
    while (adj[v].size() > 0){
        auto [w, edge] = adj[v].back();
        adj[v].pop_back();
        if (deleted_edges[edge]) continue;
        deleted_edges[edge] = 1;    
        dfs(w,res);
    }
    res.push_back(v);
}

void eulerian_cycle(int n, int m){
    if (out_deg[1] != in_deg[1] + 1 || in_deg[n] != out_deg[n] + 1) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (i == 1 || i == n) continue;
        if (in_deg[i] != out_deg[i]) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }
    vector<int> res;
    dfs(1, res);
    if (res.size() != m + 1){
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    for (int i = res.size() - 1; i>=0; --i){
        cout<<res[i]<<" ";
    }
    cout<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n, m;
    cin >> n >> m;
    int id = 0;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].emplace_back(b,id);
        id++;
        in_deg[b]++;
        out_deg[a]++;
    }

    eulerian_cycle(n,m);
    return 0;
}
