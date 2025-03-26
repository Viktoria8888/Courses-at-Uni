#include "bits/stdc++.h"
using namespace std;
#define mod 1e9 + 7
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
#define F first
#define S second
#define PB push_back
#define INF 1'000'000'000 + 10

using vi = vector<int>;
const int N = 2 * 100'000 + 10;
ll arr[N];
ll tab[N][18];
int l;
void preprocess(int n){
	l = static_cast<int>(log2(n));
	fill(&tab[0][0], &tab[0][0] + N * 18, INF);
	rep(i,n){
		tab[i][0] = arr[i];
	}
	repi(j,1,l + 1){
		rep(i,n){
			if (i + (1 << (j - 1)) < n) {
                tab[i][j] = min(tab[i][j - 1], tab[i + (1 << (j - 1))][j - 1]);
            } else {
                tab[i][j] = tab[i][j - 1]; 
            }
		}
	}
}


void solve(){
	int a,b; cin>>a>>b;
	a--;b--;
	if (a==b){
		cout<<arr[a]<<endl;
		return;
	} 
	int log_len = static_cast<int>(log2(b-a+1));
	// cout<<"przedzial: "<<a+1<<" "<<b+1<<" ";
	cout<<min(tab[a][log_len], tab[b-(1<<log_len)+1][log_len])<<endl;

}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T, n; cin>>n>>T;
	rep(i,n){
		cin>>arr[i];
	}
	preprocess(n);
	// repi(j,0,l+1){
	// 	cout<<"Level 2^ :"<<j<<endl;
	// 	rep(i,n){
	// 		cout<<"i: "<<i<<" "<<tab[i][j]<<" | ";
	// 	}
	// 	cout<<endl;
	// }
	while (T--) {
		solve();
	}
	return 0;
}