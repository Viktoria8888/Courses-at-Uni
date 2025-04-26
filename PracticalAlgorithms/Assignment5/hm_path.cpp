#include "bits/stdc++.h"
using namespace std;
const int MOD = 1e9 + 7;
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
#define F first
#define S second
#define PB push_back
#define INF 1000000000000000003
const int N = 20;
int dp[(1<<N)][N];
using vi = vector<int>;
vi adj[N];
vi adj_rev[N];

void solve(int n, int& count){

	for (int m = 1; m < (1<<n); m++){
		for (int end = 0; end < n; end++){
			if (!((1<<end)&m)) continue; // if the end is not set.

			for (const auto prev: adj_rev[end]){
				if (!((1<<prev)&m)) continue;

				// get the previous dp state for prev mask

				int m_prev = m ^ (1<<end); // removes bit at position end;
				
				dp[m][end] = max(dp[m][end], dp[m_prev][prev] + 1);
				
				
			}

		}



	}

}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	
	
	int n,m;
	cin>>n>>m;
	rep(start, n){
        dp[1 << start][start] = 1;
    }
	rep(i,m){
		int a,b;
		cin>>a>>b;
		a--;b--;
		adj[a].push_back(b);
		adj_rev[b].push_back(a);
	}
	int count = 0;
	solve(n,count);
	
	rep(i,n){
		cout<<"i: "<<i<<" "<<dp[(1<<n)-1][i]<<endl;
		count += (dp[(1 << n) - 1][i] == n - 1);
		
	}
	cout<<count % MOD <<endl;
	return 0;
}