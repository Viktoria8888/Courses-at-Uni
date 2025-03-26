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
const int N = 1000000 + 3;
using vi = vector<int>;
int phi[N];
void solve(){
    int x;cin>>x;
    cout<<phi[x]<<endl;
}
    

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;

    repi(i,1,N){
        phi[i] = i;
    }
    for (int i = 2; i<N; i++){
        if (phi[i]==i){

        for (int j=i; j<N; j+=i){
            // cout<<"phi i:"<<i<<" "<<"phi j:"<<phi[j]<<endl;
            phi[j]-=phi[j]/i;
        }}
    }

    while (T--) {
        solve();
    }
    return 0;
}