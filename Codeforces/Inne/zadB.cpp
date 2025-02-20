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
    string a;
    cin>>a;
    string res;
    for (auto& c: a){
        if (c == 'p'){
            res+='q';
        }
        else if (c == 'q'){
            res+='p';
        }
        else{
            res+='w';
        }
    }
    cout<<res<<endl;
    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while (T--) {
        solve();
    
    }
    return 0;
}