#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
const int N = 1000000 + 1;
int pi[N];

void compute_prefix_function(const string& p) {
    int m = p.size();
    pi[0] = 0;
    int k = 0;
    for (int q = 1; q < m; ++q) {
        while (k > 0 && p[k] != p[q]) {
            k = pi[k - 1];
        }
        if (p[k] == p[q]) {
            ++k;
        }
        pi[q] = k;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string p;
    cin >> p;
    
    compute_prefix_function(p);
    
    set<int> s;
    

    int len = pi[p.size() - 1];
    while (len > 0) {
        s.insert(len);
        len = pi[len - 1];
    }
    
    for (const auto& pref : s) {
        cout << pref << " ";
    }
    
    return 0;
}