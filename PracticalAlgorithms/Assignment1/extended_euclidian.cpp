#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll gcd = extended_gcd(b, a % b, x1, y1);
    
    x = y1;
    y = x1 - (a / b) * y1;
    
    return gcd;
}

void solve() {
    ll a, b;
    cin >> a >> b;

    ll x, y;
    ll gcd = extended_gcd(a, b, x, y);

    cout << x << " " << y << " " << gcd << endl;  
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>> T;
    while (--T){
        solve();    
    }
    solve();
    return 0;
}
