#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

using namespace std;
vector<pair<int,int>> count_elem(vector<int>& v){
    std::map<int, int> freq1;
    std::for_each(v.begin(), v.end(), [&freq1](int e) { freq1[e]++; });

    std::map<int, std::vector<int>> freq2;
    std::for_each(freq1.begin(), freq1.end(), [&freq2](const auto &entry) {
        freq2[entry.second].push_back(entry.first);
    });
    // Getting the last elements. The map sorts elements in an ascending order by default
    auto last = freq2.end();
    --last;

    vector<pair<int,int>> res;
    for (auto& n: last->second){
        res.emplace_back(n,last->first);
    }
    return res;
}

int main(){
    vector<int> vec1 = {1, 5, 3, 5, 8, 9, 5, 8, 8, 5};
    vector<pair<int,int>> res = count_elem(vec1);
    for (auto& e: res){
        cout<<e.first<<" : "<<e.second<<endl;
    }
    cout<<"-----------------------------\n";
    vector<int> vec2= {1, 1, 3, 5, 8, 9, 5, 8, 5};
    vector<pair<int,int>> res2 = count_elem(vec2);
    for (auto& e: res2){
        cout<<e.first<<" : "<<e.second<<endl;
    }
    return 0;
}
