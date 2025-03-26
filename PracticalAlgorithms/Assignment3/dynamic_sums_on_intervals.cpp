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
const int N = 200'000;
int arr[N];
using vi = vector<int>;
int b,b_num;
ll block_sum[N];
void solve(){
    int k, a, b;
    cin>>k>>a>>b;
    if (k == 2){

    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,T;
    cin>>n>>T;
    // the size od the block
    b = static_cast<int>(std::sqrt(n));
    // number of blocks
    b_num = n/b;
    rep(i,n){
        cin>>arr[i];
    }
    for (int i = 0; i<n; i+=b){
        for (int j = i; j < i+b; j++){
            block_sum[i]+=arr[j];
        }
    }
    // rep(i,n){
    //     cout<<"i: "<<i<<" "<<block_sum[i]<<endl;
    // }
    
    // while (T--) {
    //     solve();
    // }
    return 0;
}