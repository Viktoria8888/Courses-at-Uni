#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
const int N = 100000 + 3;
vector<pair<ll,int>> adj[N]; // first elem of the pair is the weight
ll dist[N];

void dijkstra(int n,int m)
{
    priority_queue<pair<ll,int>,vector<pair<ll,int>>, greater<>> pq;
    pq.emplace(0,1);
    for (int i = 0; i< m; i++){
        ll w;
        int u,v;
        cin>>u>>v>>w;
        adj[u].emplace_back(w,v);
    }

    while (!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (const auto& [weight_uv, v]: adj[u]){
            if (dist[u] + weight_uv < dist[v] ){
                dist[v] = dist[u] + weight_uv;
                pq.emplace(dist[v],v);
            }
        }
    }


}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n,m;
    cin>>n>>m;
    dist[1]=0;
    for (int i = 2; i<=n;i++){
        dist[i] = LLONG_MAX;
    }
    dijkstra(n,m);
    for (int i = 1; i<=n;i++){
        cout<<dist[i]<<" ";
    }
    return 0;
}