#include <iostream>
#define l1 long long
using namespace std;

int main() {
    locale::global(locale(""));

    wstring polish_chars = L"ążźćęłóśń";
    wcout<<polish_chars<<endl;
    return 0;
}
