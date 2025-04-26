#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
#define rep(i,n) for (int i = 0; i < n; ++i)

typedef long long ll;
const int N = 20;
ll dp[(1 << N)][N]; // dp[mask][end] = number of paths ending at 'end' with visited nodes in 'mask'
vector<int> adj[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    int n, m;
    cin >> n >> m;

    rep(i, m) {
        int a, b;
        cin >> a >> b;
        a--; b--;  
        adj[a].push_back(b);
    }
   
    dp[1][0] = 1; // each path starts at 0 !!!
    
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {   
            if (!(mask & (1 << u))) continue; 
            
            for (int v : adj[u]) {
                if (mask & (1 << v)) continue; 
                
                int new_mask = mask | (1 << v);
                dp[new_mask][v] = (dp[new_mask][v] + dp[mask][u]) % MOD;
            }
        }
    }
   
    int full_mask = (1 << n) - 1;
    cout << dp[full_mask][n-1] << endl; 

    return 0;
}
