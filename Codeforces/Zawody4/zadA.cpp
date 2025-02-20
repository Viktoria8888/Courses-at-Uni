#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

#include <iostream>
#include <algorithm>

int main()
{
    int t; cin >> t;
    int res = 0;
    set<string> currNames;
    map<string, string> users;
    while (t--) {
         // curr old: first old: new now
        string old, new1;
        cin >> old >> new1;
        if (currNames.count(old) > 0) {
            currNames.erase(old);

        }
        else {
            users[old] = old;
        }
        currNames.insert(new1);
  
        users[new1] = users[old];

    }
    cout << currNames.size()<<endl;
    for (auto& name : currNames) {
        cout << users[name] << " " << name << endl;
    }
}


