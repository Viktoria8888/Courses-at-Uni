#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
using namespace std;
int gcd(int a, int b){
    return (a==0) ? b :gcd(b%a,a);
}
int totient(int n){
    int c;
    for (int i = 1 ; i <= n;i++){
        if (gcd(i,n) == 1){c++;}
    }
    return c;

}

int main() {
    int k;
    cin>>k;
    vector<int> res(k);
    iota(res.begin(), res.end(), 1);
    transform(res.begin(), res.end(), res.begin(), [](int& a){return totient(a);});
    std::ofstream of("phi.txt");

    std::ostream_iterator<int> out_it (of,"; ");
    std::copy ( res.begin(), res.end(), out_it );
    return 0;
}
