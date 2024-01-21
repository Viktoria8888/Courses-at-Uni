#include <iostream>
#include <iomanip>
#include <locale>
#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;

void printInfo(const locale& loc) {
    // Ustawienie lokalizacji
    cout.imbue(loc);

    // Wypisanie liczb całkowitych i zmiennopozycyjnych
    cout << "Integer: " << 123456 << "\n";
    cout << "Floating point: " << fixed << setprecision(2) << 12345.6789 << "\n";

    // Wypisanie wartości pieniężnych
    cout << "Money: " << put_money("123456") << "\n";

    // Wypisanie bieżącej daty i godziny
    auto now = system_clock::now();
    time_t current_time = system_clock::to_time_t(now);
    cout << "Date and Time: " << put_time(localtime(&current_time), "%c") << "\n";

    cout << "--------------------------\n";
}

int main() {
    try {
        printInfo(locale("en_US"));
        printInfo(locale("fr_FR"));
        printInfo(locale("ja_JP"));
    } catch (const std::exception& e) {
        cout << "Locale not supported on this system: " << e.what() << endl;
    }

    return 0;
}
