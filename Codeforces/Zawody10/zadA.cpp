#include <iostream>
#include <string>
#include <cmath>
using namespace std;

typedef long long ll;
const int MAXS = 200010;

string A, B;
int F[MAXS][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> A >> B;

    for (int i = 1; i <= B.size(); i++) {
        for (int j = 0; j < 2; j++) {
            F[i][j] = F[i - 1][j];
        }
        ++F[i][B[i - 1] - '0'];
    }

    ll res = 0;

    for (int i = 0; i < A.size(); i++) {
        int c = A[i] - '0';

        for (int j = 0; j < 2; j++) {
            int freq_in_window = F[B.size() - A.size() + i + 1][j] - F[i][j];
            res += abs(c - j) * freq_in_window;
        }
    }

    cout << res << '\n';
    return 0;
}