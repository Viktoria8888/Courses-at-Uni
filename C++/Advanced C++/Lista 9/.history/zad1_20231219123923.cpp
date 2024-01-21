#include <iostream>
#include <iterator>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    vector<double> nums;
    // auto it = back_inserter(nums);
    // *it = 123; lines.push_back(123)

    copy(istream_iterator<double>(cin), istream_iterator<double>(), back_inserter(nums));
    // double avg = accumulate(nums.begin(), nums.end(),0)/nums.size();
    double sum = std::accumulate(nums.begin(), nums.end(), 0.0);

    // Calculate the average
    double avg = sum / nums.size();
    cout<<fixed<<setprecision(10);
    cout<<avg<<endl;
    return 0;
}
