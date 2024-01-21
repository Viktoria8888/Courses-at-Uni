#include <iostream>
#include <vector>
#include <cmath>

// ax^2 + bx + c
std::vector<double> zeros(double a, double b, double c)
{
    int discriminant = b * b - 4 * a * c;
    if (discriminant >= 0)
    {
        if (discriminant > 0)
        {
            double sqrt_delta = std::sqrt(discriminant);
            return {
                (-b - sqrt_delta) / 2 * a,
                (-b + sqrt_delta) / 2 * a,
            };
        }
        else
        {
            return {(-b) / 2 * a};
        }
    }
    else
    {
        return {};
    }
}

int main()
{
    double a, b, c;
    std::cout << "Input the values a, b, c: ";
    std::cin >> a >> b >> c;
    std::vector<double> res = zeros(a, b, c);
    if (res.empty())
    {
        std::cout << "There are no zeros" << std::endl;
    }
    std::cout << "The result is: ";
    for (const auto &z : res)
    {
        std::cout << z << " ";
    }
    std::cout << std::endl;

    return 0;
}
