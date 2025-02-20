#include "bits/stdc++.h"
using namespace std;



int main() {
    int T;
    int count = 0;
    int diff = 0;
    cin>>T;
    while (T--) {
        count=0;
        int a,b;
        cin>>a>>b;
        if (a!=b){
        
        
        int diff = abs(a-b);
        while (diff){
            if (diff >= 5){
                count += diff / 5;
                diff %=5;

            }
            else if (diff >=2){
                count += diff/ 2;
                diff %=2;
            }
            else{
                diff--;
                count++;
            }
        }}
        
       cout<<count<<endl;
    }
    return 0;
}