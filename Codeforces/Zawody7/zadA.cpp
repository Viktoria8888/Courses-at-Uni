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

const int N = 1000 + 7;
int a[N];
int b[N];

bool canBakeM(int n, int k, int m){
    ll magic_needed = 0;
    for (int i = 0 ; i< n; ++i){
        ll needed_ing = 1LL *a[i]*m;
        
        if (needed_ing > b[i]){
            magic_needed += needed_ing - b[i];
        }   
        if (magic_needed > k){
            return false;
        }
    }
    return true;

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k; cin>>n>>k;
    int mini = N;
    rep(i,n){
        cin>>a[i];
    }
    rep(i,n){
        int c; cin>>c;
        b[i] = c;
        mini = min(b[i]/a[i], mini);
    }
    int res = mini;
    int i = mini + 1;
    while(true){
        if (canBakeM(n,k,i)){
            i++;
            res++;
        }
        else{
            break;
        }
    }
    // cout<<mini<<endl;
    cout<<res<<endl;


    return 0;
}