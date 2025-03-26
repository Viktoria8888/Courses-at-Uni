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
const int N = 200000 + 1;
using vi = vector<int>;

struct node
{
    set<int>* elems;
    ll c;
};

vi adj[N];
node tab[N];
int res[N];
void dfs(int v, int p){

    for (auto neigh: adj[v]){
        if (neigh == p){
            continue;
        }
        dfs(neigh, v);
        res[neigh] = tab[neigh].elems->size();
        if (tab[neigh].elems->size() > tab[v].elems->size()){
            swap(tab[neigh].elems, tab[v].elems);
        }
        tab[v].elems->insert(tab[neigh].elems->begin(), tab[neigh].elems->end());
        
    }

}
void solve(){
    int n; cin>>n;
    repi(i,1,n+1){
        int color;cin>>color;
        tab[i].c = color;
        tab[i].elems = new set<int>({color});
    }
    rep(i,n-1){
       int a,b;cin>>a>>b;
       adj[a].push_back(b);
       adj[b].push_back(a);
    }
    dfs(1, -1);
    res[1] = tab[1].elems->size();
    repi(i,1,n+1){
        cout<<res[i]<<" ";
    }
    cout<<endl;


}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}