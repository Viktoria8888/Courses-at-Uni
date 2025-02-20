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
const int N = 100;
int R[N]; 



int Find(int x ){
	if (R[x] !=x){
	    R[x] = Find (R[x]);}
	return R[x];
}
void Union(int a, int b) {
	R[Find(a)] = Find(b);
}

void solve(){
   
    int n;
    cin>>n;
     rep(i,n) 
    {R[i] = i;}
    vector<pair<int,int>> coors;
    rep(i,n){
        int x,y;cin>>x>>y;
        coors.push_back({x,y});
    }
    sort(coors.begin(), coors.end());
    rep(i,n){
        repi(j,i+1,n){
            if (coors[i].F == coors[j].F || coors[i].S == coors[j].S){
                Union(i,j);
            }
          
        }
    }
    int count = n;
    rep(i,n){
        if (Find(i) !=i){
            count--;
        }
    }
    cout<<count-1<<endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    solve();
    
    return 0;
}