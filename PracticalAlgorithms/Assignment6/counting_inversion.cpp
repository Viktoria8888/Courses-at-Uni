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
void modify(int ind, int value){
	ind +=s;
	T[ind]+=value;
	for (; ind > 1; ind >>=1){
		T[ind>>1 ] = T[ind] + T[ind^1]; 
	}
}
//r exculsive
ll query(int l, int r){
	ll res = 0;
	l+=s; r+=s;
	for (;l<r;l>>=1,r>>=1){
		if (l&1) {
			res += T[l++];
		}
		if (r&1){
			res += T[--r];
		}
	}
	return res;
}

void solve(int n,int maxi){
	ll res = 0;
	modify(arr[0],1);
	repi(i,1,n){
		res+=query(arr[i]+1, maxi+1);
		modify(arr[i],1);
		// cout<<i<<endl;
		// rep(i,(maxi*2) + 2){
		// 	cout<<"i: "<<i<<" " <<T[i]<<endl;
		// }
	}

	cout<<res<<endl;
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;cin>>n;
	
	int maxi = -1;
	rep(i,n){
		cin>>arr[i];
		maxi = max(maxi,arr[i]);
	}
	for (s = 1; s< maxi; s<<=1 );
	// cout<<endl;
	// cout<<s<<endl;
	// cout<<maxi<<endl;
	// build(s);

	solve(n,maxi);

	// rep(i,(maxi*2) + 2){
	// 	cout<<"i: "<<i<<" " <<T[i]<<endl;
	// }
	return 0;
}