#include <iostream>
#include <vector>

using namespace std;

template<int a, int b>
struct GCD{
    enum{
        val = GCD<b,b%a>::val
    };
};
// template<>
// struct GCD<0, 0> {
//     enum { val = 0 };
// };

template<int a>
struct GCD<a, 0> {
    enum { val = a };
};

template<int b>
struct GCD<0, b> {
    enum { val = b };
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<GCD<12,4>::val<<endl;
    return 0;
}
