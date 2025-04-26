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
using vi = vector<int>;
int T[N][N];
int dp[(1<<N)];
// row - person; column - machine
void solve(int n){	
	rep(num,n){
		for (int m = 0; m<(1<<n); m++){
			if (__builtin_popcount(m) != num) continue;
			rep(i,n){
				if ((1<<i)&m){ // the machine is not free
					continue;
				}
				int m_prim = m | (1<<i); // set the bit
				dp[m_prim] = max(dp[m_prim],dp[m] + T[num][i]);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	rep(i,n){
		rep(j,n){
			cin>>T[i][j]; 
		}
	}
	
	
	solve(n);
	// rep(i,(1<<n)){
	// 	cout<<dp[i]<<endl;
	// }
	cout<<dp[(1<<n) -1]<<endl;
	return 0;
}