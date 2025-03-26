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
const int N = 100000+5;
using vi = vector<int>;

int partition(vi& A, int l, int r){
    int i = l-1;
    int j = r+1;
    int elem = A[l];
      while (true) {
        do { i++; } while (A[i] < elem);  
        do { j--; } while (A[j] > elem);  
        
        if (i >= j) {
            return j;  
        }
        
        swap(A[i], A[j]);  
    }
}
int partition_r(vi& arr, int low, int high)
{

	srand(time(NULL));
	int random = low + rand() % (high - low);
	swap(arr[random], arr[low]);

	return partition(arr, low, high);
}

void quicksort(vi& arr, int l, int r){
    if (l<r){
        int k = partition_r(arr,l,r);
        quicksort(arr,l,k);
        quicksort(arr,k+1,r);
    }

}
void solve(){
    int n;cin>>n;
    vi arr;
    rep(i,n){
        int a; cin>>a;
        arr.push_back(a);
    }
    quicksort(arr,0,n-1);
    rep(i,n){
        cout<<arr[i]<<" ";
    }
    cout<<endl;

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}