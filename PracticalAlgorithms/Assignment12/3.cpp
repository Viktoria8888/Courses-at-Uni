#include <iostream>
#include <string>
#include <vector>
using namespace std;

string longestPalindrome(const string &s)
{
    if (s.empty())
        return "";

    string processed = "^#";
    for (char c : s)
    {
        processed += c;
        processed += '#';
    }
    processed += '$';

    int n = processed.length();
    vector<int> P(n, 0);
    int center = 0, right = 0;

    for (int i = 1; i < n - 1; i++)
    {
        int mirror = 2 * center - i;

        if (i < right)
        {
            P[i] = min(right - i, P[mirror]);
        }

        while (processed[i + (1 + P[i])] == processed[i - (1 + P[i])])
        {
            P[i]++;
        }

        if (i + P[i] > right)
        {
            center = i;
            right = i + P[i];
        }
    }

    int maxLen = 0;
    int centerIndex = 0;
    for (int i = 1; i < n - 1; i++)
    {
        if (P[i] > maxLen)
        {
            maxLen = P[i];
            centerIndex = i;
        }
    }

    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string T;
    cin >> T;

    cout << longestPalindrome(T) << endl;

    return 0;
}