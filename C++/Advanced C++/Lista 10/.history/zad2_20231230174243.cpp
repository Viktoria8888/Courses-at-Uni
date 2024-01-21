#include <iostream>
#include <iomanip>
#include <locale>
#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;

void printInfo(const string& loc) {
    locale::global(locale(loc));


    cout << "Integer: " << 123456 << "\n";
    cout << "Floating point: " << fixed << setprecision(2) << 12345.6789 << "\n";

    cout << "Money: " << put_money("123456") << "\n";


    auto now = system_clock::now();
    time_t current_time = system_clock::to_time_t(now);
    cout << "Date and Time: " << put_time(localtime(&current_time), "%c") << "\n";

    cout << "--------------------------\n";
}

int main() {
    try {
        printInfo("en_US.UTF-8");
        printInfo("fr_FR.UTF-8");
        printInfo("ja_JP.UTF-8");
    } catch (const std::exception& e) {
        cout << "Locale not supported on this system: " << e.what() << endl;
    }

    return 0;
}
