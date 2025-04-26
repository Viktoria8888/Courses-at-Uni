#include "bits/stdc++.h"
using namespace std;
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
#define F first
#define S second
#define PB push_back
using vi = vector<int>;
const int N = 200000 + 1;
const int MAX_K = 19;
const int M = 200000 + 1;
int change[N];
vector<pair<int,int>> path;
vi adj[N];
int ans[N];
bool TEST = true;

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
            int p = parent[i];
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
void test(){

}
void count_paths(int node, int p) {
    for (const auto& neigh: adj[node]) {
        if (neigh != p) {
            count_paths(neigh, node);
            change[node]+=change[neigh];
        }
    }
}
void solve(int n, const vi& parent){
    EulerTour euler(n,parent);
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
    for (const auto& [f,s] : path){
        change[f]++;
        change[s]++;
        int l = lca(f,s);
        change[l]--;
        if (l != 1) change[parent[l]]--;
    }

    count_paths(1,-1);

}
void print_result(int n, vi& parent){
     solve(n,parent);
     for (int i = 1; i<=n; i++){
       cout<<change[i]<<" ";
     }
    cout<<'\n';

}
void build_parent(int node, int p, vi& parent) {
    parent[node] = p;
    for (int neigh : adj[node]) {
        if (neigh != p) {
            build_parent(neigh, node, parent);
        }
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    vi parent(n+1,-1);
    rep(i,n-1){
      int v,u;cin>>v>>u;
      adj[v].push_back(u);
      adj[u].push_back(v);
    }
    build_parent(1,-1,parent);
    rep(i,m){
       int v,u;cin>>v>>u;
       path.emplace_back(v,u);
    }
    print_result(n,parent);

    return 0;
}