#include <bits/stdc++.h>
using namespace std;
set<int> get_divisors(int x) {
    set<int> s;
    for (int i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            s.insert(i);
            s.insert(x / i);
        }
    }
    return s;
}

int main() {
    int n, t;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> A(n);
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }

        int k = -1;

        for (int j = 0; j < n; j++) {
            int minA = A[j];
            int eqMinA = count(A.begin(), A.end(), minA);

      
            if (eqMinA >= n / 2) {
                k = -1; 
                break;  
            }

            map<int, int> divsA;
            for (int i = 0; i < n; i++) {
                if (A[i] > minA) {
                    for (auto& d : get_divisors(A[i] - minA)) {
                        divsA[d]++;
                    }
                }
            }

      
            for (auto p : divsA) {
                if (p.second >= n / 2 - eqMinA) {
                    k = max(k, p.first);
                }
            }
        }

        cout << k<< endl;  
    }

    return 0;
}
