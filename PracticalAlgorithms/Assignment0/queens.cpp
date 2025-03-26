#include "bits/stdc++.h"
using namespace std;
#define mod 1e9 + 7
#define rep(i,n) for (int i = 0; i < n; ++i)
#define repi(i,s,n) for (int i = s; i < n; ++i)
typedef long long ll;
#define F first
#define S second
#define PB push_back
const int N = 12;
using vi = vector<int>;
int board[N] = {-1};
// board[i] = k - there is a queen at (k,i);
bool is_safe(int r, int c){
    rep(i,c){
        if (r==board[i] || abs(r-board[i])==abs(c-i)){
            return false;
        }
    }
    return true;

}
void dfs(int c, int& count, int n){
    if (c == n){
        count++;
    }
    rep(r,n){
        if (is_safe(r,c)){
            board[c] = r;
            dfs(c+1,count,n);
            //backtracking
            board[c] = -1;
        }
    }


}
void solve(){
    int n; cin>>n;
    int count = 0;
    dfs(0,count,n);
    cout<<count<<endl;

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fill(board, board + N, -1);
    solve();
    return 0;
}