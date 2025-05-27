#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
const int N = 100000;

vector<int> adj[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> indegree(n + 1, 0); 
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            pq.push(i);
        }
    }

    vector<int> res;
    while (!pq.empty()) {
        int v = pq.top();
        pq.pop();
        res.push_back(v);
        for (int u : adj[v]) {
            indegree[u]--;
            if (indegree[u] == 0) {
                pq.push(u);
            }
        }
    }

    if ((int)res.size() < n) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int v : res) {
            cout << v << " ";
        }
        cout << "\n";
    }

    return 0;
}