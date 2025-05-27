#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve(){
    ll x1,y1,x2,y2,x3,y3;
    cin>>x1>>y1>>x2>>y2>>x3>>y3;
    double dist_p1_p2 = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

    ll cross = (x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);
    // cout<<endl;
    cout<<setprecision(10)<<abs((double)cross/dist_p1_p2)<<endl;
}

int main() {

    int q; cin>>q;
    for (int i = 0; i< q ; i++){
        solve();
    }
    return 0;
}