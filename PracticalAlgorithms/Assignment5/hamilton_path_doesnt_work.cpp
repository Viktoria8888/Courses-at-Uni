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
const int N = 20;
int dp[(1<<N)][N];
using vi = vector<int>;
vi adj[N];

bool is_set(int i, int x){
	return ((1<<i)&x) == 1;
}
void dfs(int v,int parent, int n){
	
	for (const auto& u: adj[v]){
		if (u == parent) continue;
		// cout<<"v: "<<v<<" u: "<<u<<endl;

		for (int m = 1; m<(1<<n); m++){
			if (!is_set(u,m) && is_set(v,m)){
				int m_prim = m | (1<<u);
				dp[m_prim][u] = max(dp[m_prim][u], dp[m][v] + 1);
			}
		}
		dfs(u,v,n);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	cin>>n>>m;
	rep(i,m){
		int a,b;
		cin>>a>>b;
		a--;b--;
		adj[a].push_back(b);
	}
	dfs(0,-1,n);
	// rep(j,(1<<n)){
	// 	rep(i,n){
	// 		cout<<"i: "<<i<<" "<<dp[j][i]<<endl;
	// 	}
	// }
	rep(j,(1<<n)){
		cout<<j<<endl;
		rep(i,n){
			cout<<"i: "<<i<<" "<<dp[(1<<n)-1][i]<<endl;
		}
	}
	cout<<dp[(1<<n)-1][n-1]<<endl;
	return 0;
}