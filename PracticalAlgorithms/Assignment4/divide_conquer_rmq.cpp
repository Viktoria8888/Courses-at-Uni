#include "bits/stdc++.h"
using namespace std;
#define mod 1e9 + 7
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
#define F first
#define S second
#define PB push_back
#define INF 1000000000 + 1
const int N = 200000;
using vi = vector<int>;
ll ans[N];
ll arr[N];
ll pref[N];
ll suff[N];
struct Query{
	int l;
	int r;
	int i;
	Query(int l1, int r1, int idx) : l(l1), r(r1), i(idx) {}

};


void d_and_c(vector<Query>& query, int l, int r){
	if (query.empty() || l > r){
		return;
	}
	if (l == r) {
        for (const Query& q : query) {
            if (q.l == l && q.r == r) {
                ans[q.i] = arr[l];
            }
        }
        return;
    }
	int m = l + (r-l)/2;
	vector<Query> L,R;

	if (m+1 <= r){
		pref[m + 1] = arr[m + 1];
    for (int i = m + 2; i <= r; i++) { 
        pref[i] = min(pref[i - 1], arr[i]);
    }
	}
	

    suff[m] = arr[m];
    for (int i = m - 1; i >= l; i--) {
        suff[i] = min(suff[i + 1], arr[i]);
		// cout<<suff[i]<<endl;
    }
	rep(i,query.size()){
		Query q = query[i];
		// if (q.i != INF
		if (q.l <= m && q.r <= m){
			L.push_back(q);
		}
		else if (q.l > m && q.r > m ){
			R.push_back(q);
		}
		else{ // q.l <= m  and q.r > m 
			// cout<<pref[r]<<" "<<suff[l]<<" ";
			ans[q.i] = min(pref[q.r],suff[q.l]);
			// cout<<ans[q.i]<<endl;
		}
	}
	// middle_queries(M,m,l,r);}
	d_and_c(L,l,m);
	d_and_c(R,m+1,r);
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,T;
	cin>>n>>T;
	rep(i,n){
		cin>>arr[i];
	}
	vector<Query> queries;

	rep(i,T){
		int a,b;cin>>a>>b;
		a--;b--;
		queries.push_back(Query(a,b,i));
	}
	d_and_c(queries,0,n-1);
	rep(i,T){
		cout<<ans[i]<<endl;
	}
	
	return 0;
}