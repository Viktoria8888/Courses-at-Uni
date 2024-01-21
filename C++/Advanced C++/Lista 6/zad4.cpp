#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
using namespace std;
void printHistogram(const map<char, double> &freq)
{
    for (const auto &entry : freq)
    {
        int barLength = static_cast<int>(entry.second*500);
        cout << entry.first << ": ";
        cout << fixed << setprecision(4) << entry.second << " ";
        cout << string(barLength, '*') << endl;
    }
}
int main(int argc, char const *argv[])
{

    std::ifstream inputFile(argv[1]);
    vector<string> lines;
    std::copy(
        istream_iterator<std::string>(inputFile),
        istream_iterator<std::string>(),
        back_inserter(lines));

    inputFile.close();
    int num_letters = 0;
    map<char, double> freq;
    for (auto &line : lines)
    {
        for_each(line.begin(), line.end(), [&freq, &num_letters](char &a)
                 {
            if (isalpha(a)){
            freq[tolower(a)]++;
            num_letters++;} });
    }
    // Dividing each count by the number of letters

    for_each(freq.begin(), freq.end(), [&num_letters](auto& entry){entry.second/=num_letters;});


    printHistogram(freq);
    return 0;
}
