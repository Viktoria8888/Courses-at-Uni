#include <iostream>
#include <vector>
using namespace std;

#include <iostream>
#include <algorithm>
void DFS(vector<int>& vis, vector<vector<int>>& g, vector<int>& gold, int start, int& min1) {
    vis[start] = 1;
    for (auto& n : g[start]) {
        if (!vis[n]) {
            min1 = gold[n]< min1? gold[n]: min1;
            DFS(vis, g,gold, n, min1);
        }
    }

}

int main()
{
    cout << "Hello World!" << endl;;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
