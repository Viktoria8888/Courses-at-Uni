#include <iostream>
#include <vector>
using namespace std;

const int SMALL = -1000000000;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];

    vector<vector<int>> previous_dp(n, vector<int>(n, SMALL));
    vector<vector<int>> current_dp(n, vector<int>(n, SMALL));
    previous_dp[0][0] = grid[0][0];

    for (int steps = 1; steps < 2 * (n - 1) + 1; steps++) {
        for (int pos1 = 0; pos1 < n; pos1++) {
            int x1 = pos1, y1 = steps - x1;
            if (y1 < 0 || y1 >= n) continue;

            for (int pos2 = 0; pos2 < n; pos2++) {
                int x2 = pos2, y2 = steps - x2;
                if (y2 < 0 || y2 >= n) continue;

                int points = grid[x1][y1];
                if (x1 != x2 || y1 != y2) points += grid[x2][y2];

                int max_prev = SMALL;
                for (int dx1 = -1; dx1 <= 0; dx1++) {
                    for (int dx2 = -1; dx2 <= 0; dx2++) {
                        int prev_x1 = x1 + dx1;
                        int prev_x2 = x2 + dx2;
                        if (prev_x1 >= 0 && prev_x1 < n && prev_x2 >= 0 && prev_x2 < n) {
                            max_prev = max(max_prev, previous_dp[prev_x1][prev_x2]);
                        }
                    }
                }
                current_dp[x1][x2] = max(current_dp[x1][x2], max_prev + points);
            }
        }

        swap(previous_dp, current_dp); // previous_dp = current_dp 

        for (int i = 0; i < n; i++)    // current_dp = SMALL
            fill(current_dp[i].begin(), current_dp[i].end(), SMALL);
    }

    cout << previous_dp[n - 1][n - 1];
    return 0;
}