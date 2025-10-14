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
    cin>>p;
    compute_prefix_function(p);
    set<int> s;
    for (int i = 0; i<p.size(); i++){
        cout<<pi<i
        s.insert(pi[i]);
    }
    for (const auto& pref: s){
        if (pref != 0 && pref != p.size()){
            cout<<pref<<" ";
        }
    }


    return 0;
}
