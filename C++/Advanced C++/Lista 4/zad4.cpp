#include <iostream>
#include <functional>
#include <utility>

using std::cout, std::endl;
// n_chose_negNUM = 0
int main()
{
    std::function<int(int, int)> n_choose_k;
    n_choose_k = [&n_choose_k](int n, int k)
    {
        return (k< 0) ? 0 : ((k == 0 || k == n) ? 1 : n_choose_k(n - 1, k) + n_choose_k(n - 1, k - 1));
    };
    int result1 = n_choose_k(5, 2);
    int result2 = n_choose_k(5,-1);
    cout << "C(" << 5 << ", " << 2 << ") = " << result1 << endl;
    cout << "C(" << 5 << ", " << -1 << ") = " << result2 << endl;
}
