#include <iostream>
using std::cout, std::endl;
auto call_in_order = [](auto f, auto g)
{
    return [f,g](auto x)
    {
        f(x);
        g(x);
    };
};

int square(int &x)
{
    x = x * x;
    cout << "Square function. Result = " << x << endl;
    return x;
}

int increment(int &x)
{
    x = x + 1;
    cout << "Increment function.  Result = " << x << endl;
    return x;
}
int mult_10(int &x)
{
    x *= 10;
    cout << "Multiplied function by 10.  Result = " << x << endl;
    return x;
}
int main()
{

    call_in_order( call_in_order(square, increment), mult_10)(1);

    return 0;
}
