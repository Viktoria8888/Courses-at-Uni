#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cin >> n;
   
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
   
    vector<int> last_occurrence(1000001, 0);  
    long long sum = 0;
   
    for(int i = 1; i <= n; i++) {
        int x = a[i-1];
        sum += 1LL * (i - last_occurrence[x]) * 2 * (n - i + 1) - 1;
        last_occurrence[x] = i;
    }
   
    cout.precision(10);
    cout << fixed << 1.0 * sum / (1LL * n * n) << endl;
   
    return 0;
}