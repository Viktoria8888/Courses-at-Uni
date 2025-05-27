#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007

const int N = 100000;
int scc_id[N + 1];  

void dfs(int node, vector<int> &finish_order, vector<vector<int>> &adj, vector<bool> &visited) {
    visited[node] = true;
    for (auto &v : adj[node]) {
        if (!visited[v]) {
            dfs(v, finish_order, adj, visited);
        }
    }
    finish_order.push_back(node);
}

void rev_dfs(int node, vector<vector<int>> &radj, vector<bool> &visited, int scc_count) {
    scc_id[node] = scc_count;
    visited[node] = true;
    for (auto &v : radj[node]) {
        if (!visited[v]) {
            rev_dfs(v, radj, visited, scc_count);
        }
    }
}

pair<vector<ll>, vector<vector<int>>> find_scc(int n, int m, vector<vector<int>>& adj, vector<vector<int>>& radj, vector<int>& a, vector<pair<int,int>>& edges) {
    vector<int> finish_order;
    vector<bool> visited(n + 1, false);
    
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, finish_order, adj, visited);
        }
    }
    
    
    reverse(finish_order.begin(), finish_order.end());
    
    fill(visited.begin(), visited.end(), false);
    int scc_count = 0;
    
    for (int v : finish_order) {
        if (!visited[v]) {
            rev_dfs(v, radj, visited, scc_count);
            scc_count++;
        }
    }

    vector<ll> scc_sum(scc_count, 0);
    for (int i = 1; i <= n; i++) {
        scc_sum[scc_id[i]] += a[i];
    }
    
    vector<vector<int>> condensed_graph(scc_count);
    set<pair<int,int>> added_edges; 
    
    for (auto& edge : edges) {
        int u = edge.first, v = edge.second;
        int scc_u = scc_id[u], scc_v = scc_id[v];
        
        if (scc_u != scc_v && added_edges.find({scc_u, scc_v}) == added_edges.end()) {
            condensed_graph[scc_u].push_back(scc_v);
            added_edges.insert({scc_u, scc_v});
        }
    }
    
    return {scc_sum, condensed_graph};
}

ll max_path_sum(int node, vector<ll>& scc_sum, vector<vector<int>>& graph, vector<ll>& memo) {
    if (memo[node] != -1) {
        return memo[node];
    }
    
    ll max_child_sum = 0;
    for (int child : graph[node]) {
        max_child_sum = max(max_child_sum, max_path_sum(child, scc_sum, graph, memo));
    }
    
    memo[node] = scc_sum[node] + max_child_sum;
    return memo[node];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> adj(n + 1);
    vector<vector<int>> radj(n + 1);
    vector<int> a(n + 1);
    vector<pair<int,int>> edges;
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
        edges.push_back({u, v});
    }
    
    auto [scc_sum, condensed_graph] = find_scc(n, m, adj, radj, a, edges);
    
    int scc_count = scc_sum.size();
    vector<ll> memo(scc_count, -1);
    
    ll max_result = 0;
    for (int i = 0; i < scc_count; i++) {
        max_result = max(max_result, max_path_sum(i, scc_sum, condensed_graph, memo));
    }
    
    cout << max_result << endl;
    
    return 0;
}