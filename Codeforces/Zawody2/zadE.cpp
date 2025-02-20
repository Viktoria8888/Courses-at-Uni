#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>


using namespace std;

#include <iostream>

int main() {

	int n, m;
	cin >> n >> m;
	vector<int> cost;
	vector<int> bill100(n, 0);
	vector<int> bill1(n, 0);
	for (int i = 0; i < n; i++) {
		int c; cin >> c;
		bill100[i] = c / 100;
		cost.push_back(c%100);
	}
	vector<long long> w;
	for (int i = 0; i < n; i++) {
		int w_i; cin >> w_i;
		w.push_back(w_i);
	}
	priority_queue<pair<int,int> , vector<pair<int, int>>, greater<pair<int,int>>> pq; // kolejka z kar¹
		

	long long penalty = 0;
	for (int i = 0; i < n; i++) {
		if (cost[i] == 0) {
			continue;
		}

		pq.emplace(make_pair((100 - cost[i]) * w[i],i ));
		if (m - cost[i] >= 0) {
			m -= cost[i];
			bill1[i] = cost[i];
		}
		else {
			pair<int, int> p = pq.top();
			penalty += p.first;
			m += 100 - cost[i]; // pay for cost[i] after getting 100 monets
			bill100[p.second] += 1;
			bill1[p.second] -= cost[p.second];
			bill1[i] += cost[i];
			pq.pop();


		}
	}
	cout << penalty << endl;
	for (int i = 0; i < n; i++) {
		cout << bill100[i] << " " << bill1[i] << endl;
	}

	return 0;
}