#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
const int N = 100000 + 3;
vector<int> adj[N];
vector<int> radj[N]; // reversed edges
ll dist[N];
bool reachable_from_1[N], reachable_to_n[N];


struct edge {
    int u,v;
    ll w;
    edge(int _u, int _v, ll _w): u(_u), v(_v), w(_w)  {}
};

void initialize(int n) {
    dist[1]=0;
    for (int i = 2; i<=n;i++){
        dist[i] = LLONG_MIN;
    }
}

void dfs1(int u) {
    reachable_from_1[u] = true;
    for (int v : adj[u]) {
        if (!reachable_from_1[v]) dfs1(v);
    }
}

void dfs2(int u) {
    reachable_to_n[u] = true;
    for (int v : radj[u]) {
        if (!reachable_to_n[v]) dfs2(v);
    }
}


ll bellman_ford(int n, int m, vector<edge>& edges)
{
    initialize(n);
    dfs1(1);
    dfs2(n);
    for (int i = 1; i <= n-1; i++) {
        for (int j = 0; j <m; j++) {
            edge e = edges[j];
            if (dist[e.u] != LLONG_MIN && dist[e.v]< dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    for (int j = 0; j <m; j++) {
        edge e = edges[j];
        if (dist[e.u] != LLONG_MIN && dist[e.v]< dist[e.u] + e.w) {

            if (reachable_from_1[e.v] && reachable_to_n[e.v]) return -1;
        }
    }


    return dist[n];
}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n,m;
    cin>>n>>m;
    initialize(n);
    vector<edge> edges;
    for (int i = 0; i< m; i++){
        ll w;
        int u,v;
        cin>>u>>v>>w;
        edges.emplace_back(u,v,w);
        adj[u].emplace_back(v);
        radj[v].emplace_back(u);
    }
    cout<<bellman_ford(n,m,edges)<<'\n';
    return 0;
}