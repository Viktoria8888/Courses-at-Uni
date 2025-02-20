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
const int N = 100000;
int degree[N];

void solve(){
    int n;
    cin>>n;
    vector<pair<int,int>> edges;
    rep(i,n-1){
        int a,b;
        cin>>a>>b;
        a--;b--;
        edges.push_back({a,b});
        degree[a]++;
        degree[b]++;
    }
    int curr  = n-2;
    int found = -1;
    int node3 = 0;
    for (auto& [f,s]: edges){
        if (found == -1 && degree[f] == 3){
            found = f;
        }
        else if (found == -1 && degree[s] == 3){
            found = s;
        }
        if (found > -1 &&  (f == found || s == found)){
            cout<<node3<<endl;
            node3++;
        }
        else{
            cout<<curr<<endl;
            curr--;
        }
    }
    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}