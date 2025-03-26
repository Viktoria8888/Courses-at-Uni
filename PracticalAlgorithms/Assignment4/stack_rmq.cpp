#include "bits/stdc++.h"
using namespace std;
#define mod 1e9 + 7
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
#define F first
#define S second
#define PB push_back
#define INF 1000000000000000003
const int N = 200000;
using vi = vector<int>;
ll arr[N];
ll suff[N];
ll ans[N];
int n;
void write_answers(vector<pair<pair<int,int>,int>>& queries,vector<pair<int,int>> q,int start, int end){
	// Now it is time to write answers.
	// Use upper_bound: returns the first element < than l and then step back
	// tp achieve the first index <= l
	for (int i = start; i <= end; i++){
		auto [p, index] = queries[i]; 
        auto [l, r] = p;
		auto it = std::upper_bound(q.begin(), q.end(), l, 
                           [](int value, const pair<int, int>& p) {
                               return value < p.F; 
                           });

		if (it == q.begin()){cout<<"what"<<endl;}
		--it;
		ans[index] = (*it).S; // take the actual value;
	}
}


void solve(vector<pair<pair<int,int>,int>>& queries){
	vector<pair<int,int>> q;

	int end = queries.back().F.S;
	// na którym indeksie kończy się jakaś grupa;
	stack<pair<int,int>> ends; // end index in arr, end index in query;
	ends.push({end, queries.size() - 1});

	for (int i = queries.size() - 2; i >= 0; i--){
		auto [p, index] = queries[i]; 
        auto [f, s] = p;
		if (s != end){
			ends.push({s,i});
			end = s;
		}
	}

	
	auto [end_arr,end_query] = ends.top();
	// cout<<"s: "<<s<<endl;

	ends.pop();
	// cout<<"arr["<<s<<" : "<<arr[s]<<endl;
	suff[end_arr] = arr[end_arr];
	for (int i = end_arr-1; i>= 0; i--){
		suff[i] = min(suff[i+1], arr[i]);
	}
	rep(i,n){
		cout<<"i: "<<i<<" : "<<suff[i]<<endl;
	}
	// Starting structure is created

	q.push_back({0, suff[0]});
	for (int i = 1; i <= end_arr; i++){
		if (suff[i-1] == suff[i]) continue;
		q.push_back({i, suff[i]});
	}

	
    // for (auto& [f,s]: q){
	// 	cout<<f<<" "<<s<<endl;
	// }
    // cout << endl;

	write_answers(queries, q, 0,end_query);

	int start_query = end_query + 1; // to know which queryis to answer
	int start_arr = end_arr + 1;
	while (!ends.size()){
		auto [end_arr, end_query] = ends.top();
		ends.pop();

		for (int i = start_arr; i <= end_arr; i++){
			int new_index;
			while (q.size() > 0 && (q.back().S > arr[i])){
				new_index = q.back().F;
				q.pop_back();
			}
			q.push_back({new_index, arr[i]});
		}
		write_answers(queries, q, start_query, end_query);
	}



	
	

	

}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin>>n>>T;
	rep(i,n){
		cin>>arr[i];
	}
	// <<a,b>,i>
	vector<pair<pair<int,int>,int>> queries;
	rep(i,T){
		int a,b;
		a--;b--;
		cin>>a>>b;
		queries.push_back({{a,b},i});
	}
	sort(queries.begin(), queries.end(), 
     [](const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
         return a.first.second < b.first.second;
     });
	rep(i,n){
		suff[i] = LLONG_MAX;
	}
	solve(queries);
	rep(i,T){
		cout<<ans[i]<<endl;
	}

	return 0;
}
 modufy my code