#include <iostream>
#define l1 long long
using namespace std;

int main() {
    locale::global(locale(""));

    wstring polish_chars = L"Język polski używa znaków diakrytycznych, takich jak ą, ć, ę, ł, ń, ó, ś, ź, ż.";
    wcout<<polish_chars<<endl;
    return 0;
}
