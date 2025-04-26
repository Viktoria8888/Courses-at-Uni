#include "bits/stdc++.h"
using namespace std;
#define mod 1e9 + 7
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
#define F first
#define S second
#define PB push_back
#define INF 1000000000000000003
const int N = 200000;
using vi = vector<int>;
vi adj[N];
int dp_in[N], dp_out[N];

void dfs(int node, int parent) {

    for (const auto& v : adj[node]) {
        if (v == parent) continue;
        dfs(v, node);
        dp_out[node] += max(dp_in[v], dp_out[v]); 
    }
	int maxi = 0;
    for (const auto& v : adj[node]) {
        if (v == parent) continue;
        maxi =  max(maxi, 1 + dp_out[v] + dp_out[node] - max(dp_in[v], dp_out[v]));
    }
    dp_in[node] = maxi;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;

    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    rep(i, n - 1) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1);
    cout << max(dp_out[0], dp_in[0]) << endl;

    return 0;
}
