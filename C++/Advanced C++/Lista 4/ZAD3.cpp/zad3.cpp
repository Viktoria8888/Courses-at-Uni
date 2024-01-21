#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <functional>
#include <string>
#include "Average.cpp"
#include "PrintInRange.hpp"
#include "PrintKthElem.hpp"
#include "MaxMin.cpp"
#include "SumElements.cpp"
using namespace std;

int main()
{
    vector<double> c1 = {1, 0.42, 3.14, 5.4, 7, 8, 8.42, 9, 10};
    // list<string> c2 = {"implication", "excess", "complex", "accept", "detailed", "fragile"};
    list<string> c2 = {"a", "ba", "c", "d", "bb"
                                            "e",
                       "f", "g"};
    set<int> c3 = {1, 2, 3, 4, 5, 7};
    cout << "Printing in range" << endl;
    for_each(c1.begin(), c1.end(), PrintInRange(3, 9));
    cout << "------------------" << endl;
    for_each(c2.begin(), c2.end(), PrintInRange("b", "f"));
    cout << "------------------" << endl;
    for_each(c3.begin(), c3.end(), PrintInRange(2, 5));
    cout << endl;
    cout << "Printing k-th value" << endl;
    for_each(c1.begin(), c1.end(), PrintKthElem(2, 4));
    cout << endl;
    cout << "Calculating average" << endl;
    Average<double> avg_calc1;
    for_each(c1.begin(), c1.end(), [&avg_calc1](int value)
             { avg_calc1(value); });
    double res = avg_calc1.get_avg();
    cout << "The average for c1 is: " << res << endl;

    Average<double> avg_calc3;
    for_each(c3.begin(), c3.end(), [&avg_calc3](int value)
             { avg_calc3(value); });
    double res3 = avg_calc3.get_avg();
    cout << "The average for c3 is: " << res3 << endl;
    cout << endl;

    cout << "Finding min-max values: " << endl;
    MaxMin<double> vals1;
    for_each(c1.begin(), c1.end(), [&vals1](double val)
             { vals1(val); });
    pair<double, double> res_max_min = vals1.getMinMax();
    cout << "Max: " << res_max_min.first << " Min: " << res_max_min.second << endl;
    cout << "For strings: " << endl;
    MaxMin<string> vals2;
    for_each(c2.begin(), c2.end(), [&vals2](string val)
             { vals2(val); });
    pair<string, string> res_max_min2 = vals2.getMinMax();
    cout << "Max: " << res_max_min2.first << " Min: " << res_max_min2.second << endl;
    cout << endl;
    cout << "Summing all the elements" << endl;
    SumElements<double> sum1;
    for_each(c1.begin(), c1.end(), [&sum1](double val)
             { sum1(val); });
    double sum1_res = sum1.get_sum();
    cout << "Sum for vector od doubles: " << sum1_res << endl;
    SumElements<string> sum2;
    for_each(c2.begin(), c2.end(), [&sum2](string val)
             { sum2(val); });
    string sum2_res = sum2.get_sum();
    cout << "Sum for strings: " << sum2_res << endl;
}
