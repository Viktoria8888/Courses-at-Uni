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
const int N = 100000+1;
const int M = 200000+1;
using vi = vector<int>;
int maxi = 1;

struct node{
    int size;
    int f;

};
node tab[N];
void init(int n){
    repi(i,1,n+1){
        tab[i].size = 1;
        tab[i].f = i;
    }
}
int find(int a){
    if (tab[a].f == a){
        return a;
    }

    int father = find(tab[a].f);
    tab[a].f = father;
    return father;
}

void onion(int a, int b){
    int aR = find(a), bR = find(b);
    if (aR == bR){
        return;
    }
    if (tab[aR].size < tab[bR].size){
        swap(aR, bR);
    }
    tab[bR].f = aR;
    tab[aR].size += tab[bR].size;
    maxi = max(maxi, tab[aR].size);
}

void solve(){
    int n,m; cin>>n>>m;
    init(n);
    int c = n;
    rep(i,m){
        int a,b;cin>>a>>b;
        int aR = find(a), bR = find(b);
        if (aR != bR){
            c--; 
            onion(a,b);
        }
        cout<<c<<" "<<maxi<<endl;
    }
    

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}