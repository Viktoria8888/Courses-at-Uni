#include "bits/stdc++.h"
#include <cassert>
using namespace std;
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
const int N = 200000 + 10;
const int MAX_K = 19;
bool TEST = false;

class EulerTour {
private:
    vector<vector<int>> adj;
    int n;
    int TIME = 1;
public:
    vector<int> start;
    vector<int> end;
    EulerTour(const int _n, const vector<int>& parents): n(_n), start(n+1,-1),end(n+1, -1) {
        adj.resize(n + 1);
        for (int i = 2; i<=n; i++) {
            adj[i].push_back(parents[i]);
            adj[parents[i]].push_back(i);
        }
        dfs(1,-1);
    }
    void dfs(int node, int p) {
        start[node] = TIME++;
        for (const auto& neigh: adj[node]) {
            if (neigh != p) {
                dfs(neigh, node);
            }
        }
        end[node] = TIME++;
    }
    bool is_ancestor(int v, int u) {
        if (v==u) return true;
        return start[v] < start[u] && end[v] > end[u];
    }
};

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
    // 2^k
    bool is_ancestor_exists(int v, int k) {
        return T[v][k] != -1;
    }
};

void test_euler(int n, const vector<int>& parent) {
    EulerTour e(n,parent);
    assert(e.is_ancestor(4,1)==0);
    assert(e.is_ancestor(1,2)==1);
    assert(e.is_ancestor(5,1)==0);
    assert(e.is_ancestor(1,1)==0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> parent(n + 1, -1);
    for (int i = 2; i <= n; ++i) {
        cin >> parent[i];
    }

    EulerTour euler(n, parent);
    BinaryLifting bl(n, parent);

    auto lca = [&](int v, int u) {
        if (euler.is_ancestor(v, u)) return v;
        if (euler.is_ancestor(u, v)) return u;

        for (int i = MAX_K - 1; i >= 0; i--) {
            if (!bl.is_ancestor_exists(v, i)) {
                continue;
            }
            int possible_jump_vertex = bl.binary_lifting(v, 1 << i);
            if (!euler.is_ancestor(possible_jump_vertex, u)) {
                v = possible_jump_vertex;
            }
        }
        return parent[v];
    };

    while (q--) {
        int v, k;
        cin >> v >> k;
        cout << lca(v, k) << '\n';
    }

    return 0;
}