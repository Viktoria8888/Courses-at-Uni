#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
const int N = 100000;
const int M = 200000;
int name[N];
pair<int, int> edges[M];

void dfs(int node, vector<int> &st, vector<vector<int>> &adj, vector<bool> &visited)
{
    visited[node] = true;
    for (auto &v : adj[node])
    {
        if (!visited[v])
        {
            dfs(v, st, adj, visited);
        }
    }
    st.push_back(node);
}

void revdfs(int node, vector<vector<int>> &adj, vector<bool> &visited, int count)
{
    name[node] = count;
    visited[node] = true;
    for (auto &v : adj[node])
    {
        if (!visited[v])
        {
            revdfs(v, adj, visited, count);
        }
    }
}
pair<vector<ll>, vector<vector<int>>> scc(int m, int n, vector<vector<int>> &adj, vector<vector<int>> &radj, vector<int> &a)
{
    vector<int> pseudo;
    vector<bool> vis(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        if (vis[i])
            continue;
        dfs(i, pseudo, adj, vis);
    }
    reverse(pseudo.begin(), pseudo.end());
    fill(vis.begin(), vis.end(), false);
    int count = 0;
    
    for (const auto &v : pseudo)
    {
        if (vis[v])
            continue;
        count++;
        revdfs(v, radj, vis, count);
    }
    
    vector<ll> scc_sum(count + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        scc_sum[name[i]] += a[i];
    }
    
    vector<vector<int>> condensed_graph(count+1);
    set<pair<int,int>> added_edges; 
    
    for (int i = 0; i < m; i++) {
        auto& edge = edges[i];
        int u = edge.first, v = edge.second;
        int scc_u = name[u], scc_v = name[v];
        if (scc_u != scc_v && added_edges.find({scc_u, scc_v}) == added_edges.end()) {
            condensed_graph[scc_u].push_back(scc_v);
            added_edges.insert({scc_u, scc_v});
        }
    }
    
    return {scc_sum, condensed_graph};
}


ll greatest_sum_on_path(int node,vector<ll>& scc_sum, vector<vector<int>> &g, vector<ll>& dp)
{
    if (dp[node] != -1){
        return dp[node];
    }
    ll max_child = 0;
    for (auto &v : g[node])
    {
        max_child = max(max_child, greatest_sum_on_path(v, scc_sum, g, dp));
    }
    
    dp[node] = scc_sum[node] + max_child;
    return dp[node];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> adj(n + 1);
    vector<vector<int>> radj(n + 1);
    vector<int> a(n + 1);
    
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
        edges[i] = {u, v};
    }
    
    for (int i = 0; i <= n; i++)
    {
        name[i] = -1;
    }
    
    auto [scc_sum, condensed_graph] = scc(m, n, adj, radj, a);
    
    vector<ll> dp(scc_sum.size(), -1);
    ll max_result = 0;

    for (int i = 0; i < scc_sum.size(); i++) {
        if (scc_sum[i] > 0) {
            max_result = max(max_result, greatest_sum_on_path(i, scc_sum, condensed_graph,dp));
        }
    }
    
    
    cout << max_result << endl;
    return 0;
}