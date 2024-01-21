#include <iostream>
using namespace std;
int gcd(int a, int b){
    return (a==0) ? b :gcd(b%a,a);
}
int totient(int a){
    int c;
    for (int i = 1 ; i <= a;i++){
        if (gcd(i,a) == 1){c++;}
    }
    return c;

}

int main() {
    cout<<totient(83);
    return 0;
}
