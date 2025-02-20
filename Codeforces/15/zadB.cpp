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
const int N = 5 * 100000 + 3;
const char maxi = 'z' + 2;
char smaller[N]; // less[i] - the smaller value than ith character
// Ann wins if can move left
// it doesn't payoff to move right
//'', 'a', 'a',''
// '', '', 
// find if there is a smaller character to the left of ith index.

void solve(){
    string s;
    cin>>s;
    smaller[0] = maxi;
    repi(i,1,s.size()){
        smaller[i] = min(smaller[i-1], s[i-1]);
    }

    // rep(i,s.size()){
    //     cout<<"i: " << i<<" "<<smaller[i]<<endl;}
    // cout<<endl;
    rep(k,s.size()){
        if (smaller[k] == maxi || smaller[k]==s[k] || smaller[k] > s[k]){
            cout<<"Mike"<<endl;
        }
        else{
            cout<<"Ann"<<endl;
        }
    }
    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}