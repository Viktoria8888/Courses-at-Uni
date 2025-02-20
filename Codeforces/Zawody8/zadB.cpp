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
const int N = 10000;

void solve(){
    int n;
    ll k;
    cin>>n>>k;
    ll count = 0;
    queue<int> q;
    int maxi = -1;
    rep(i,n){
        int a; cin>>a;
        maxi = max(maxi, a);
        q.push(a);
    }

    int winner = q.front();
    if (k>=n-1){
        cout<<maxi<<endl;
        return;
    }
    q.pop();
    int num = 0;
        while(!q.empty()){
        int s = q.front();  
        q.pop();
        // cout<<"next: "<<s<<endl;
        if (winner < s){
            winner = s;
            num = 1;
        }
        else{
            num++;
        }
        if (num == k){
            break;
        }
        
        
    }
    cout<<winner<<endl;
   

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
   
    solve();
   
    return 0;
}