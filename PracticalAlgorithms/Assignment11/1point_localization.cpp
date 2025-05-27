#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
void solve()
{
    ll x1,y1,x2,y2,x3,y3;
    cin>>x1>>y1>>x2>>y2>>x3>>y3;
    ll cross = (x2 - x1)*(y3 - y1) - (y2 - y1)*(x3 - x1);

    if (cross == 0) {
        cout << "TOUCH" << endl;
    } else if (cross < 0) {
        cout << "RIGHT" << endl;
    } else {
        cout << "LEFT" << endl;
    }
    
    
}



int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    int q;cin>>q;
    for (int i = 0; i< q; i++){
        solve();
    }
    return 0;
}
