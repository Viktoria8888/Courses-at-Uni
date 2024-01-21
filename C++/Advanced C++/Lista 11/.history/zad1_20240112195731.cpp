#include <iostream>
#include <vector>

using namespace std;
template<int N>
struct Lucas{
    enum {
        val = Lucas<N-1>::val + Lucas<N-2>::val};
};
template<>
struct Lucas<0>
{
    enum {val = 2 };
};
template<>
struct Lucas<1>
{
    enum {val = 1};
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<Lucas<10>::val<<endl;
    return 0;
}
