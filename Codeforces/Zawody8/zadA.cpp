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
    int n; cin>>n;
    
    vector<int> p(n);
    rep(i,n){
        cin>>p[i];
    }
    if (n==1){
        cout<<-1<<endl;
        return;
    }
    vector<int> q = p;
    sort(q.begin(), q.end());
    rep(i,n-1){
        if (p[i]==q[i]){
            swap(q[i], q[i+1]);
            
        }
    }
    if (q[n-1] == p[n-1]){
        swap(q[n-2], q[n-1]);
    }
    // cout<<"RES: ";
    rep(i,n){
        cout<<q[i]<<' ';
    }
    cout<<endl;
    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while (T--) {
    
        solve();}
        // cout<<endl;
    return 0;
}