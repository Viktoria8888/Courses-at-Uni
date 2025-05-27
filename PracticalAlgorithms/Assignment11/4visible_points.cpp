#include <bits/stdc++.h>
using namespace std;
#define ll long long

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int xq; cin >> xq;  
    int n; cin >> n;
    
    set<pair<int, int>> slopes;
    
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        int dx = x - xq;
        int dy = y;  
     
        int g = gcd(abs(dx), abs(dy));
        dx /= g;
        dy /= g;
    
        slopes.insert({dy, dx});
    }
    
    cout << slopes.size() << "\n";
    
    return 0;
}