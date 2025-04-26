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
int h[N];
int diam[N];
vi adj[N];
void dfs(int node, int parent){
	// cout<<node<<endl;
	int maxH1 = -1, maxH2 = -1;
	for (const auto& v: adj[node]){
		if(v == parent) continue;
		dfs(v,node);
		h[node] = max(h[node], h[v] + 1);
		if (h[v] > maxH1){
			maxH2 = maxH1;
			maxH1 = h[v];
			diam[node] = max(diam[v], diam[node]);
		}
		else if (maxH2 == -1){
			maxH2 = h[v];
		}
	}
	diam[node] = max(maxH1 + maxH2 + 2, diam[node]);

}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	rep(i,n-1){
		int a,b;
		cin>>a>>b;
		a--;b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(0, -1);
	cout<<diam[0]<<endl;
	return 0;
}