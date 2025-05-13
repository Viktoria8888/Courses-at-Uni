#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500 + 3;
ll dist[N][N];

void floyd_warshall(const int n) {

    for (int k = 1; k<=n; k++) {
        for (int i = 1; i<=n; i++) {
            for (int j = 1; j<=n; j++) {
                if (dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}
void solve() {
    int u, v;
    cin>>u>>v;
    if (dist[u][v] == LLONG_MAX) cout<<"-1"<<endl;
    else cout<<dist[u][v]<<endl;
}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    int n,m,q;
    cin>>n>>m>>q;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i==j) dist[i][j] = 0;
            else dist[i][j] = LLONG_MAX;
        }
    }

    for (int i = 0; i< m; i++){
        ll w;
        int u,v;
        cin>>u>>v>>w;
        dist[u][v] = min(dist[u][v],w);
        dist[v][u] = min(dist[u][v],w);

    }

    floyd_warshall(n);
    for (int i = 0; i< q; i++) {
        solve();
    }
    return 0;
}