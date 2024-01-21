#include <iostream>
#include <iomanip>
#include <locale>
#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;

void printInfo(const locale &loc)
{

    cout.imbue(loc);

    cout << "Integer: " << 123456 << "\n";
    cout << "Floating point: " << fixed << setprecision(2) << 12345.6789 << "\n";

    cout << "Money: " << put_money("13456") << "\n";
    cout << "Money: " << put_money("3543") << "\n";

    auto now = system_clock::now();
    time_t current_time = system_clock::to_time_t(now);
    cout << "Date and Time: " << put_time(localtime(&current_time), "%c") << "\n";
    cout << "Date and Time: " << put_time(localtime(&current_time), "%c") << "\n";
    cout << "--------------------------\n";
}

int main()
{

    printInfo(locale("en_US.UTF-8"));
    printInfo(locale("fr_FR.UTF-8"));
    printInfo(locale("ja_JP.UTF-8"));

    return 0;
}
