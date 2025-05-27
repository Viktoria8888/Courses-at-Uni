#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
const int N = 100000;
vector<int> adj[N];
int vis[N];

bool dfs(int v)
{
    cout << v << endl;
    if (vis[v])
    {
        return true;
    }
    vis[v] = 1;
    int next;
    if (adj[v].size() > 0)
    {
        next = adj[v].back();
        adj[v].pop_back();
        auto it = std::find(adj[next].begin(), adj[next].end(), v);
        if (it != adj[next].end())
        {
            adj[next].erase(it);
        }
        return dfs(next);
    }

    return false;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cout << "is cycle " << dfs(1) << endl;
    return 0;
}
