#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
const int N = 100000 + 3;
ll dist[N];
int parent[N];

struct edge {
    int u,v;
    ll w;
    edge(int _u, int _v, ll _w): u(_u), v(_v), w(_w)  {}
};

void initialize(int n) {
    dist[1]=0;
    for (int i = 2; i<=n;i++){
        dist[i] = 0;
        parent[i] = -1;
    }
}


vector<int> bellman_ford(int n, int m, vector<edge> &edges)
{
    vector<int> cycle;
    initialize(n);

    for (int i = 1; i <= n-1; i++) {
        for (int j = 0; j <m; j++) {
            edge e = edges[j];
            if (dist[e.u] != LLONG_MAX && dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                parent[e.v] = e.u;
            }
        }
    }

    int cycle_vertex = -1;
    for (int j = 0; j <m; j++) {
        edge e = edges[j];
        if (dist[e.u] != LLONG_MAX && dist[e.v] > dist[e.u] + e.w) {
            cycle_vertex = e.v;
            parent[e.v] = e.u;
            break;
        }
    }

    if (cycle_vertex == -1) {return {};}
    for (int i = 0; i < n; ++i)
        cycle_vertex = parent[cycle_vertex];

    int c = cycle_vertex;
    cycle.push_back(c);
    c = parent[cycle_vertex];
    while (c != cycle_vertex) {
        cycle.push_back(c);
        c = parent[c];

    }
    cycle.push_back(c);
    reverse(cycle.begin(), cycle.end());
    return cycle;
}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n,m;
    cin>>n>>m;
    vector<edge> edges;
    for (int i = 0; i< m; i++){
        ll w;
        int u,v;
        cin>>u>>v>>w;
        edges.emplace_back(u,v,w);
    }
    vector<int> cycle = bellman_ford(n,m,edges);
    if (!cycle.size()) {cout<<"NO"<<endl; return 0;}
    cout<<"YES"<<endl;
    for (const auto& e: cycle) {
        cout<<e<<" ";
    }

    return 0;
}