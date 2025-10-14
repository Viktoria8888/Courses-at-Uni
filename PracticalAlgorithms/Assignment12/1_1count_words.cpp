#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;
const ll base = 41;

vector<ll> computePrefixHashes(const string &s, vector<ll> &power) {
    int n = s.size();
    vector<ll> hash(n + 1, 0);
    power[0] = 1;
    for (int i = 0; i < n; ++i) {
        hash[i + 1] = (hash[i] * base + (s[i] - 'a' + 1)) % mod;
        power[i + 1] = (power[i] * base) % mod;
    }
    return hash;
}


ll getSubstringHash(const vector<ll> &hash, const vector<ll> &power, int l, int r) {
    return (hash[r] - hash[l - 1] * power[r - l + 1] % mod + mod) % mod;    
}

void solve(string &t, string &p) {
    int n = t.size(), m = p.size();
    if (m > n) {
        cout << 0 << '\n';
        return;
    }

    vector<ll> power(max(n, m) + 1);
    vector<ll> hashT = computePrefixHashes(t, power);
    vector<ll> hashP = computePrefixHashes(p, power);

    ll patternHash = getSubstringHash(hashP, power, 1, m);

    int count = 0;
    for (int i = 0; i <= n - m; ++i) {
        ll currentHash = getSubstringHash(hashT, power, i + 1, i + m);
        if (currentHash == patternHash) {
            count++;
        }
    }
    cout << count << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string t, p;
    cin >> t >> p;
    solve(t, p);
    return 0;
}