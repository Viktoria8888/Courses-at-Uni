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
const int N = 1000000+1;
const int M = 300000+1;
using vi = vector<int>;
int maxi = 1;

struct node{
    int size;
    int f;
    int parity; // parity od the path to the father.

};
node tab[N];
void init(int n){
    repi(i,1,n+1){
        tab[i].size = 1;
        tab[i].f = i;
        tab[i].parity = 0;
    }
}
int find(int a){
    if (tab[a].f == a){ 
        return a;
    }
    
    int father = find(tab[a].f);
    tab[a].parity = tab[tab[a].f].parity + tab[a].parity;
    tab[a].f = father;
    return father;
}

bool onion(int a, int b, int p){
    int aR = find(a), bR = find(b);
    if (aR == bR){
        return p == (tab[b].parity + tab[a].parity) %2;
    }
    if (tab[aR].size < tab[bR].size){
        swap(aR, bR);
    }
    tab[bR].f = aR;
    tab[aR].size += tab[bR].size;
    tab[bR].parity = (((p-tab[a].parity - tab[b].parity) % 2 )+ 2)% 2;
    return true; 
}

void solve(){
    int n,m; cin>>n;
    cin>>m;
    init(n);
    int count = 0;
    bool flag = true;
    rep(i,m){
        int a,b, p;cin>>a>>b>>p;
        if (flag && !onion(a,b,p)){
            flag = false;
            
        }
        if (flag){
            count++;
        }
       

    }
    cout<<count<<endl;
    

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}