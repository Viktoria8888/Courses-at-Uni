#include <iostream>
#include <vector>

using namespace std;
// Tożsamość absorbcyjna
template<int n, int k>
struct nChooseK{
    enum{
        val = n*(1/k)*nChooseK<n-1,k-1>::val
    };
};
template<int n>
struct nChooseK<n, 0> {
    enum { val = 1 };
};

template<int n>
struct nChooseK<n, n> {
    enum { val = 1 };
};

template<>
struct nChooseK<0, 0> {
    enum { val = 1 };
};








int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<nChooseK<5,2>::val<<endl;
    return 0;
}
