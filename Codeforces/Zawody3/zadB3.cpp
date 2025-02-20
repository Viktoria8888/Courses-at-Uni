#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    int t;
    cin >> t;  
    map<int, vector<int>> map;
    while (t--) {
        int n, k;
        cin >> n >> k;  

        map.clear();
         // int: min max
        for (int i = 0; i < n; ++i) {
            int a; cin >> a;
            if (map.count(i) == 0) {
                map[a].push_back(i);
                map[a].push_back(i);
            }
            else {
                map[a][0] = min(i, map[a][0]);
                map[a][1] = max(i, map[a][1]);
            }
        }

       
        for (int i = 0; i < k; ++i) {
            int a, b;
            cin >> a >> b; 
            if (map.count(a) && map.count(b)) {
                if (map[a][0] < map[b][1]) {
                    cout << "YES" << endl;
                }
                else {
                    cout << "NO" << endl;
                }
            }

        }
        

    }

    return 0;
}
