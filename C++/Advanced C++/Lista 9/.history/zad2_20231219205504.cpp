#include <iostream>
using namespace std;
int gcd(int a, int b){
    return (a==0) ? b :gcd(b%a,a);
}
int totient(int a){
    int c;
    for (int i = 2 ; i < a -1;i++){
        if (gcd(i,a) == 1){c++;}
    }
    return c;

}

int main() {
    cout<<totient(10);
    return 0;
}
