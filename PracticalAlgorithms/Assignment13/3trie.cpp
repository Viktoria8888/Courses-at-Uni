#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
const int mod = 1000000007;
const int N = 5000 + 1;
const int K = 100000;

class Trie {
public:
    bool isWord = false;
    Trie* nodes[26] = {nullptr};

    bool char_is_present(char c) {
        return nodes[c - 'a'] != nullptr;
    }

    void insert(const string& s) {
        Trie* node = this;
        for (char ch : s) {
            if (!node->char_is_present(ch)) {
                node->nodes[ch - 'a'] = new Trie();
            }
            node = node->nodes[ch - 'a'];
        }
        node->isWord = true;
    }

    int find_longest_prefix(const string& s) {
        Trie* node = this;
        int length = 0, max_length = 0;
        for (char ch : s) {
            if (node->char_is_present(ch)) {
                node = node->nodes[ch - 'a'];
                length++;
                if (node->isWord) max_length = length;
            } else {
                break;
            }
        }
        return max_length;
    }

    ~Trie() {
        for (int i = 0; i < 26; ++i) {
            delete nodes[i];
        }
    }
};


int number_of_combinations(Trie& trie, string t){
    vector<int> dp(t.size()+1,0);
    int n = t.size();
    dp[n] = 1;

    for(int i = n-1; i>=0; i--){
        Trie* node = &trie;
        for (int j = i; j < n; j++){
            char ch = t[j];
            if (!node->char_is_present(ch)){
                break;
            }
            node = node->nodes[t[j]-'a'];
            if (node->isWord){
                dp[i] = (dp[i] + dp[j+1]) % mod; 
            }
        }
    }
    return dp[0];
}

void test_insert()
{
    Trie trie;
    trie.insert("ab");
    trie.insert("abab");
    trie.insert("abc");
    trie.insert("a");
    assert(trie.find_longest_prefix("aba")==2);
    
}
void test_combinations(){
    // string t = "ababc";
    Trie trie;
    trie.insert("ab");
    trie.insert("abab");
    trie.insert("c");
    trie.insert("cb");
    cout<<number_of_combinations(trie,"ababc")<<endl;


}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string t;
    cin >> t;
    int k;
    cin >> k;
    Trie trie;
    for (int i = 0; i<k;i++){
        string s; cin>>s;
        trie.insert(s);
    }
    cout<<number_of_combinations(trie,t)% mod<<endl;
    // test_insert();
    // test_combinations();
    return 0;
}
