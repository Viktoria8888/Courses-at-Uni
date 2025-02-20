#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < n; ++i) 
#define repi(i,s,n) for (int i = s; i < n; ++i) 
using namespace std;

#define N 1008

// dp[i][0/1] - minimum cost of repanting pixels for the i-prefix of column if group color ends with 1 or 0 

int dp[N][2];

int main() {
	int n, m, x, y;
	int count[N] = { 0 };
    int prefSum[N] = { 0 };
	scanf("%d %d %d %d", &n, &m, &x, &y);
    rep(i,n) {
        char row[N];
        scanf("%s", row);  

        for (int j = 0; j < m; ++j) {
            if (row[j] == '#') {
                count[j]++;  
            }
        }
    }
 /*   rep(i, m) {
        cout << count[i] << " ";

        
    }*/


    rep(i, m) {
        prefSum[i + 1] = prefSum[i] + count[i];
    }
  /*  rep(i, m+1) {
        cout << prefSum[i] << " ";
    }
   */
    rep(i, m + 1) {
        dp[i][0] = dp[i][1] = 1e9;
    }
    dp[0][0] = 0;
    dp[0][1] = 0;
    repi(i, x, m + 1) {
        for (int j = x; j <= y && i - j >= 0; ++j) {
           
            int blackCost = prefSum[i] - prefSum[i - j];
            int whiteCost = j * n - blackCost;

            dp[i][0] = min(dp[i][0], dp[i - j][1] + blackCost);  
            dp[i][1] = min(dp[i][1], dp[i - j][0] + whiteCost); 
        }
    }
    printf("%d\n", min(dp[m][0], dp[m][1]));	
    
    return 0;

}
