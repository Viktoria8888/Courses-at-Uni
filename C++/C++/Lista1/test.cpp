#include <iostream>
using namespace std;
int main () {
cout << "[mm]: ";
double mm;
cin >> mm;
double inch = mm/25.3995;
cout << inch << endl;
cout << mm << "[mm] = " << inch << "[in]" << endl;
return 0;
}
