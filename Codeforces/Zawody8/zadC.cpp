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
    int t;cin>>t;
    multiset<int> starts;
    multiset<int> ends;
    while (t--){
        char op;
        int l,r;
        cin>>op>>l>>r;
        if (op == '+'){
            starts.insert(l);
            ends.insert(r);
        }
        else{
            auto it1 = starts.find(l);
            auto it2 = ends.find(r);
            if (it1 != starts.end() && it2 != ends.end()){
                starts.erase(it1);
                ends.erase(it2);
            }
         
        }
        if (!starts.empty() && (*ends.begin() < *starts.rbegin())){
            // cout<<"size: " <<starts.size()<<endl;
             cout<<"YES"<<endl;
            }
        else{
            cout<<"NO"<<endl;
        }
    }
    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}