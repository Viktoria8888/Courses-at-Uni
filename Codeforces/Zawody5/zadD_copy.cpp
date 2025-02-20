#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < n; ++i) 
#define repi(i, s, n) for (int i = s; i < n; ++i) 
typedef long long ll;
using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    int s = 2 * n - 2;

    // Define the 2D vector `a` to store input values
    vector<vector<int>> a(n, vector<int>(n));
    rep(i, n) {
        rep(j, n) {
            scanf("%d", &a[i][j]);
        }
    }

    // Define the 3D vector `dp` for dynamic programming
    vector<vector<vector<int>>> dp(s + 1, vector<vector<int>>(n, vector<int>(n, -1e6)));

    int x1, x2;
    dp[0][0][0] = a[0][0];

    rep(t, s + 1) {
        rep(y1, n) {
            rep(y2, n) {
                x1 = t - y1;
                x2 = t - y2;

                // Bounds check before accessing `a` or `dp` elements
                if (x1 < 0 || x1 >= n || x2 < 0 || x2 >= n) continue;

                int value = a[x1][y1] + a[x2][y2];

                if (y1 > 0 && y2 > 0)
                    dp[t][y1][y2] = max(dp[t][y1][y2], dp[t - 1][y1 - 1][y2 - 1] + value);
                if (y1 > 0)
                    dp[t][y1][y2] = max(dp[t][y1][y2], dp[t - 1][y1 - 1][y2] + value);
                if (y2 > 0)
                    dp[t][y1][y2] = max(dp[t][y1][y2], dp[t - 1][y1][y2 - 1] + value);
                
                dp[t][y1][y2] = max(dp[t][y1][y2], dp[t - 1][y1][y2] + value);

                if (x1 == x2 && y1 == y2) {
                    dp[t][y1][y2] -= a[x1][y1];
                }
            }
        }
    }

    printf("%d\n", dp[s][n - 1][n - 1]);

    return 0;
}
