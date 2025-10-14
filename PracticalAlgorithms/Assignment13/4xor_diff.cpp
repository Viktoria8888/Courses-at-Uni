#include <bits/stdc++.h>
using namespace std;

class Trie
{
public:
    Trie *children[2];
    int count;         // how many numbers end EXACTLY at this node
    int subtree_count; // how many numbers pass through this nide

    Trie()
    {
        children[0] = children[1] = nullptr;
        count = 0;
        subtree_count = 0;
    }

    void insert(int n)
    {
        Trie *node = this;
        for (int i = 31; i >= 0; i--)
        {
            int bit = (n >> i) & 1;
            if (node->children[bit] == nullptr)
            {
                node->children[bit] = new Trie();
            }
            node = node->children[bit];
            node->subtree_count++;
        }
        node->count++;
    }

    int countPairs(int num, int k)
    {
        return dfs(this, num, k, 31);
    }

private:
    int dfs(Trie *node, int num, int k, int bit_pos)
    {
        if (bit_pos < 0)
        {
            return node->count;
        }

        if (node == nullptr)
            return 0;

        int bit_num = (num >> bit_pos) & 1;
        int bit_k = (k >> bit_pos) & 1;
        int result = 0;

        if (bit_k == 1)
        {

            int needed_bit = 1 - bit_num;
            if (node->children[needed_bit] != nullptr)
            {
                result += dfs(node->children[needed_bit], num, k, bit_pos - 1);
            }
        }
        else
        {

            int opposite_bit = 1 - bit_num;
            if (node->children[opposite_bit] != nullptr)
            {
                result += node->children[opposite_bit]->subtree_count;
            }

            if (node->children[bit_num] != nullptr)
            {
                result += dfs(node->children[bit_num], num, k, bit_pos - 1);
            }
        }

        return result;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    Trie trie;
    long long total_pairs = 0;

    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;

        total_pairs += trie.countPairs(a, k);

        trie.insert(a);
    }

    cout << total_pairs << endl;
    return 0;
}