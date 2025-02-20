#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < n; ++i) 
#define repi(i,s,n) for (int i = s; i < n; ++i) 
typedef long long ll;
using namespace std;
const int N =  300 + 8;

int a[2*N][2*N];
int dp[2][2*N][2*N];
int main() {
	
	int n; scanf("%d", &n);

	int s = 2 * n - 2;
	rep(i, n) {
		rep(j, n) {
			scanf("%d", &a[i][j]);
			
		}
	}
	// rep(t, s + 1) {
	// 	rep(i, N) {
	// 		rep(j, N) {
	// 			dp[t][i][j] = -1e5;
	// 		}
	// 	}
	// }
	/*if (n == 1) {
		printf("%d", 5);
	}*/
	int x1, x2;
	
	rep(t, s + 1) {
	
		rep(i, N) {
			rep(j, N) {
				dp[t%2][i][j] = -1e7;
			}
		}
		if (t==0){
		dp[0][0][0] = a[0][0];}
		rep(y1, t+1) {
			rep(y2, t+1) {
				// x1 + y1 = t
				x1 = t - y1;
				x2 = t - y2;

				int value = a[x1][y1] + a[x2][y2];

				if (t<=0) continue;
				if (y1 > 0 && y2 > 0) dp[t%2][y1][y2] = max(dp[t %2][y1][y2], dp[(t - 1)%2][y1 - 1][y2 - 1] + value);
				if (y1 > 0) dp[t%2][y1][y2] = max(dp[t%2][y1][y2], dp[(t - 1)%2][y1 - 1][y2] + value);
				if (y2 > 0) dp[t%2][y1][y2] = max(dp[t%2][y1][y2], dp[(t - 1)%2][y1][y2 - 1] + value);
				dp[t%2][y1][y2] = max(dp[t%2][y1][y2], dp[(t - 1)%2][y1][y2] + value);
			
				if (x1 == x2 && y1 == y2) {
					dp[t%2][y1][y2] -= a[x1][y1];
				}
				// cout<<t%2 <<": " <<y1<<" "<<y2<<" " <<dp[t%2][y1][y2]<<endl;
				
			}
		}
	}

	printf("%d\n", dp[s%2][n - 1][n - 1]);

	return 0;
}