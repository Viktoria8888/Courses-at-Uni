#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#include <iostream>


int main() {
	int n, a, b, k;
	cin >> n >> a >> b >> k;
	vector<int> monsters;
	for (int i = 0; i < n; i++) {
		int m; cin >> m;
		monsters.push_back(m);
	}
	int res = 0;
	vector<int> minSkip(n, 0);
	int c = a + b;
	for (int i = 0; i < n; i++) {
		int hp = monsters[i];
		int remainder = hp % c;
		//cout << "remainder: "<< hp<<" "<< remainder << endl;
		if (remainder == 0) {
			minSkip[i] = ceil(b*1.0/a*1.0);
			//cout << "remainder: " << hp << " " << remainder <<" "<<minSkip[i] << endl;
		}
		else {
			minSkip[i] = ceil((remainder-a)*1.0/ a*1.0);
			//cout << "remainder: " << hp << " " << remainder << " " << minSkip[i] << endl;
		}
	}
	//for (int i = 0; i < n; i++) {
	//	cout << minSkip[i] << endl;
	//}
	sort(minSkip.begin(), minSkip.end());
	
	for (int i = 0; i < n; i++) {
		if (k - minSkip[i] < 0) {
			break;
		}
		k -= minSkip[i];
		res++;
	}
	cout << res << endl;
	return 0;
}
// 7-2 = 5; 5- 3= 2; 2-2=0