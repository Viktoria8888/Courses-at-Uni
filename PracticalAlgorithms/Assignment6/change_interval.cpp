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
ll T[4*(int)(1e6)];
int arr[N];
int s;
void build(int s){
	for (int i = s-1; i>0; --i){
		T[i] = T[i<<1] + T[i<<1|1];
	}
}
void modify(int l, int r, int value){
	l+=s; r+=s;
	for (;l<r;l>>=1,r>>=1){
		if (l&1) {
			T[l++]+=value;
		}
		if (r&1){
			T[--r]+=value;
		}
	}
}
//r exculsive
ll query(int ind){
	ind+=s;
	ll res = 0;
	for (;ind>=1; ind>>=1){
		res+=T[ind];
	}
	return res;
}

void solve(){
	int type; cin>>type;
	if (type == 1){
		int x,y,v;
		cin>>x>>y>>v;
		x--;y--;
		modify(x,y+1,v);
	}
	else{
		int k;cin>>k;
		k--;
		cout<<query(k)<<endl;
	}

}



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,q;cin>>n>>q;
	
	for (s = 1; s< n; s<<=1 );
	int maxi = -1;
	rep(i,n){
		cin>>T[i+s];
	}
	// cout<<endl;
	// cout<<s<<endl;
	// cout<<maxi<<endl;
	// build(s);
	// cout<<endl;
	rep(o,q){
		solve();
		
		
	}
	

	
	return 0;
}
