    #include <bits/stdc++.h>
    using namespace std;
    #define ll long long
    #define mod 1000000007
    const int N = 100000;
    int name[N];
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
    void revdfs(int node, vector<vector<int>> &adj, vector<bool> &visited,int count)
    {
        name[node] = count;
        visited[node] = true;
        for (auto &v : adj[node])
        {
            if (!visited[v])
            {
                revdfs(v, adj, visited,count);
            }
        }
    
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
        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            radj[b].push_back(a);
        }
        for (int i = 0; i <= n; i++)
        {
            name[i] = -1;
        }

        vector<int> pseudo;
        vector<bool> vis(n+1,0);
        for (int i = 1; i <= n; i++)
        {
            if (vis[i]) continue;
            dfs(i, pseudo, adj, vis);
        }
        reverse(pseudo.begin(), pseudo.end());
        vis.assign(n+1,0);
        int count = 0;
        for (const auto& v: pseudo){
            if (vis) continue;
            count++;
            revdfs(v,radj,vis,count);
        }

        int c = 1;
        vector<int> minNumInComp(count+1, -1);
        for (int i = 1; i<= n; i++){
            if (minNumInComp[name[i]] != -1) continue;
            minNumInComp[name[i]] = c++;
        }
        cout<<count<<endl;
        for (int i = 1; i<=n;i++){
            cout<<minNumInComp[name[i]]<<" ";
        }
        return 0;
    }
