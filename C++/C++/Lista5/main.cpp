#include "pixel.hpp"
using namespace std;
int main()
{
    Color col1;
    cout << "Testing constructors:" << endl;
    col1.display();

    Color col2(34, 56, 75);
    col2.display();
    cout << "Color combination of colors above:" << endl;
}
