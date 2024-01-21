#include <iostream>
#include <iterator>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <functional>
using namespace std;

int main() {
    vector<double> nums;
    // auto it = back_inserter(nums);
    // *it = 123; lines.push_back(123)
    cout<<"Input the data: "<<endl;
    copy(istream_iterator<double>(cin), istream_iterator<double>(), back_inserter(nums));
    double sum = std::accumulate(nums.begin(), nums.end(), 0.0);
    double avg = sum / nums.size();
    transform(nums.begin(),nums.end(),nums.begin(),[avg](double& x){return pow((x-avg),2);});

    double standard_deviation = sqrt(accumulate(nums.begin(), nums.end(),0.0)/nums.size());
    cout<<fixed<<setprecision(3);
    std::cout << "Average: " << avg << std::endl;
    std::cout << "Standard Deviation: " << standard_deviation << std::endl;

    return 0;
}
