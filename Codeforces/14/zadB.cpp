#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    string ternary;
    cin >> ternary;
    
    
    int zeros = 0, ones = 0, twos = 0;
    for(char c : ternary) {
        if(c == '0') zeros++;
        else if(c == '1') ones++;
        else twos++;
    }
    
    
    unordered_map<char, int> balance;
    balance['0'] = zeros - n/3;
    balance['1'] = ones - n/3;
    balance['2'] = twos - n/3;
    
    
    for(int i = 0; i < n; i++) {
        char current_char = ternary[i];
        int current_balance = balance[current_char];
        
        if(current_balance > 0) {
            if(current_char == '2') {
                if(balance['0'] < 0) {
                    ternary[i] = '0';
                    balance['0']++;
                    balance['2']--;
                }
                else if(balance['1'] < 0) {
                    ternary[i] = '1';
                    balance['1']++;
                    balance['2']--;
                }
            }
            else if(current_char == '1' && balance['0'] < 0) {
                ternary[i] = '0';
                balance['0']++;
                balance['1']--;
            }
        }
    }
    
    
    for(int i = n-1; i >= 0; i--) {
        char current_char = ternary[i];
        int current_balance = balance[current_char];
        
        if(current_balance > 0) {
            if(current_char == '0') {
                if(balance['2'] < 0) {
                    ternary[i] = '2';
                    balance['2']++;
                    balance['0']--;
                }
                else if(balance['1'] < 0) {
                    ternary[i] = '1';
                    balance['1']++;
                    balance['0']--;
                }
            }
            else if(current_char == '1' && balance['2'] < 0) {
                ternary[i] = '2';
                balance['2']++;
                balance['1']--;
            }
        }
    }
    
    cout << ternary << endl;
    
    return 0;
}