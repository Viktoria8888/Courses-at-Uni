#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;
const ll base = 911;
vector<ll> hash_prefix, power_base;

void build_hash(const string &s)
{
    int n = s.size();
    hash_prefix.assign(n + 1, 0);
    power_base.assign(n + 1, 1);
    for (int i = 0; i < n; ++i)
    {
        hash_prefix[i + 1] = (hash_prefix[i] * base + s[i]) % mod;
        power_base[i + 1] = (power_base[i] * base) % mod;
    }
}

ll get_hash(int l, int r)
{
    return (hash_prefix[r + 1] - hash_prefix[l] * power_base[r - l + 1] % mod + mod) % mod;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string t;
    cin >> t;
    int n = t.size();
    string s = t + t;
    build_hash(s);

    int best = 0;
    for (int i = 1; i < n; ++i)
    {
        int l = 0, r = n - 1, pos = -1;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            ll h1 = get_hash(best, best + mid);
            ll h2 = get_hash(i, i + mid);
            if (h1 == h2)
            {
                pos = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }

        int next_pos = (pos == -1) ? 0 : pos + 1;
        if (next_pos < n && s[best + next_pos] > s[i + next_pos])
        {
            best = i;
        }
    }

    cout << s.substr(best, n) << "\n";
    return 0;
}