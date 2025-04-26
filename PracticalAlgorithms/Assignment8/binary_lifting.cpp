
#include "bits/stdc++.h"
#include <cassert>
using namespace std;
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
const int N = 200000 + 10;
const int MAX_K = 19;
bool TEST = false;
#include "bits/stdc++.h"
using namespace std;


class BinaryLifting {
private:
    vector<vector<int>> T;
    int n;

    void init() {
        for (int k = 1; k < MAX_K; ++k) {
            for (int v = 1; v <= n; ++v) {
                if (T[v][k - 1] != -1)
                    T[v][k] = T[T[v][k - 1]][k - 1];
                else
                    T[v][k] = -1;
            }
        }
    }

public:
    BinaryLifting(int _n, const vector<int>& parent) : n(_n), T(_n + 1, vector<int>(MAX_K, -1)) {
        for (int i = 2; i <= n; ++i) {
            T[i][0] = parent[i];
        }
        init();
    }

    int binary_lifting(int v, int k) {
        for (int i = 0; i < MAX_K; ++i) {
            if (k & (1 << i)) {
                v = T[v][i];
                if (v == -1) return -1;
            }
        }
        return v;
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> parent(n + 1, -1);

    for (int i = 2; i <= n; ++i) {
        cin >> parent[i];
    }


    BinaryLifting bl(n, parent);

    while (q--) {
        int v, k;
        cin >> v >> k;
        cout << bl.binary_lifting(v, k) << '\n';
    }

    return 0;
}
