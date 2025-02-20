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
const int N = 10000+7;
int a[N];
void solve(){

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >>n;
    int s = 0;
    rep(i,n){
        cin>>a[i];
        s+= a[i];
    }
  
    if (s==1){
        cout<<-1<<endl;
        return 1;
    }
    repi(1,n){
        a[i] = a[i] + a[i-1];
    }
    int min_res = N;
    for (int i = 2; i * i <= s; i++){
        
    }

    return 0;
}