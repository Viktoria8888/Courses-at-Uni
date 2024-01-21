#include <iostream>
#include <string>
#include <vector>
using namespace std;


string bin2rzym (int x){
    const vector<pair<int, string>> rzym = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
        {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"},
        {4, "IV"}, {1, "I"}};
    string result;
    
    for (const auto &p: rzym){
        while (x >= p.first){
            result += p.second;
            x -= p.first;
        }
    }
    return result;

}

int main(){
    string input;
    while (arg)
    {
        try{
            int x= stoi(input);
        if (x>=1 && x<= 3999)
        {
            cout << bin2rzym(x)<<endl;
        }
        else{
            clog<<"invalid input: "<<x<<endl;
        }
        }
        catch (const invalid_argument &e)
        {
            clog << "Invalid input: " << input << endl;}
    }
    }