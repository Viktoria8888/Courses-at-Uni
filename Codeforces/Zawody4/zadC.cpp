#include <iostream>
#include <bits/stdc++.h>
#include <queue>
#include <algorithm>

using namespace std;

struct UF {
	bool special; // if the special node is in this set
	int size; // size to merge smaller tree to bigger one
	int parent;
	long long min_of_max;
	
};
UF tab[100000 + 7];

void init(int n) {
	for (int i = 0; i < n; i++) {
		tab[i].size = 1;
		tab[i].parent = i;
		tab[i].special = false;
		tab[i].min_of_max = -1;
	}
}

int Find(int n) {
	if (tab[n].parent == n) {
		return n;
	}
	// Path compression
	tab[n].parent = Find(tab[n].parent);
	return tab[n].parent;
}

int Union(int x, int y, long long w) {
	int a = Find(x), b = Find(y);
	if (a == b) {
		return 0;
	}
	if (tab[a].size < tab[b].size) {
		swap(a, b);
	}
	if (tab[a].special && tab[b].special) {
		tab[a].min_of_max = w;
	}
	if (tab[b].special) {
		tab[a].min_of_max = max(tab[a].min_of_max, tab[b].min_of_max);
	}ls


	tab[a].size += tab[b].size;
	tab[a].special |= tab[b].special;
	tab[b].parent = a;
	return 1;

}

class Compare {
public:
	bool operator()(pair<int, pair<int, int>>& a, pair<int, pair<int, int>>& b) {
		if (a.first > b.first) {
			return true;
		}
		return false;
	}
};

int main(){
	int n, m, k;
	cin >> n >> m >> k;
	init(n);
	vector<int> specV;
	for (int i = 0; i < k; i++) {
		int x_i; cin >> x_i;
		specV.push_back(x_i-1);
		tab[x_i-1].special = true;
		
	}
	
	priority_queue < pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, Compare> pq;
	for (int i = 0; i < m; i++) {
		long long a, b, w;
		cin >> a >> b>>w;
		pq.emplace(w, make_pair(a-1, b-1));
	}
	while (!pq.empty()) {
		auto [w, s] = pq.top();
		auto [a, b] = s;
		Union(a, b, w);
		pq.pop();
	}
	for (auto& i : specV) {
		int father = Find(i);
		cout << tab[father].min_of_max << " ";
	}
	cout << endl;
}
