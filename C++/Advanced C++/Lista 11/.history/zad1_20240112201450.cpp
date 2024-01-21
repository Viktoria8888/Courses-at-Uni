#include <iostream>
#include <vector>

using namespace std;
template<int N, int a=2,int b=1>
struct Lucas{
    enum {
        val = Lucas<N-1, b, a+b>::val };
};
template<int a,int b>
struct Lucas<0,a,b>
{
    enum {val =a };
};
template<int a,int b>
struct Lucas<1,a,b>
{
    enum {val = b};
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<Lucas<10>::val<<endl;
    return 0;
}
