#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod1 = 1e9 + 7;
const ll mod2 = 1e9 + 9;
const ll base1 = 911;
const ll base2 = 972663749;
const int N = 500005;

int n, q;
int a[N], b[N];
ll prefix_xor1_a[N], prefix_xor1_b[N];
ll prefix_xor2_a[N], prefix_xor2_b[N];

void calculate() {
    prefix_xor1_a[0] = prefix_xor1_b[0] = 0;
    prefix_xor2_a[0] = prefix_xor2_b[0] = 0;
    
    for (int i = 0; i < n; i++) {
        ll hash1_a = ((ll)a[i] * base1) % mod1;
        ll hash2_a = ((ll)a[i] * base2) % mod2;
        ll hash1_b = ((ll)b[i] * base1) % mod1;
        ll hash2_b = ((ll)b[i] * base2) % mod2;
        prefix_xor1_a[i + 1] = prefix_xor1_a[i] ^ hash1_a;
        prefix_xor2_a[i + 1] = prefix_xor2_a[i] ^ hash2_a;
        prefix_xor1_b[i + 1] = prefix_xor1_b[i] ^ hash1_b;
        prefix_xor2_b[i + 1] = prefix_xor2_b[i] ^ hash2_b;
    }
}

ll get_xor_range(ll prefix_xor[], int l, int r) {
    return prefix_xor[r + 1] ^ prefix_xor[l];
}

void solve() {
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;
    l1--; r1--; l2--; r2--;
    
    if (r1 - l1 != r2 - l2) {
        cout << "NIE\n";
        return;
    }
    
    ll xor1_a = get_xor_range(prefix_xor1_a, l1, r1);
    ll xor1_b = get_xor_range(prefix_xor1_b, l2, r2);
    ll xor2_a = get_xor_range(prefix_xor2_a, l1, r1);
    ll xor2_b = get_xor_range(prefix_xor2_b, l2, r2);
    
    if ((xor1_a == xor1_b) && (xor2_a == xor2_b)) {
        cout << "TAK\n";
    } else {
        cout << "NIE\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> q;
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    calculate();
    
    for (int i = 0; i < q; i++) {
        solve();
    }
    
    return 0;
}