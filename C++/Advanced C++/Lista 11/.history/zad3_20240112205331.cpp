#include <iostream>
#include <vector>

using namespace std;
// Tożsamość absorbcyjna
template<int a, int b>
struct GCD{
    enum{
        val = GCD<b,b%a>::val
    };
};
template<int a, int b>
struct GCD<a,0>
{
    enum {val = a};
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<GCD<12,4>::val<<endl;
    return 0;
}
