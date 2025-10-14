#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007

// int hash()
void solve(string& t, string& p)
{
    int count = 0;
    int j = 0;
    while ((size_t)j<t.size()){
        if (p[0] != t[j]){
            j++;
        }
        else{
            int same = 0;
            for (int i = 0; i<p.size(); i++){
                same+=t[j+i]==p[i];
            }
            count+=same==p.size();
            j++;
        }
    }
    cout<<count<<endl;
}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    string t,p;
    cin>>t>>p;
    solve(t,p);
    return 0;
}
