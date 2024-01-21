/*    Zdefiniuj prostą klasę zawierającą licznik typu uint64_t, początkowo ustawiony na wartość 1. W klasie tej, oprócz innych funkcjonalności, umieść wirtualny destruktor, który wypisze komunikat ze stanem licznika na standardowym wyjściu dla błędów cerr.
    Następnie stwórz n-elementową tablicę takich liczników i opakuj ją wskaźnikiem unique_ptr (opakowanie ma dotyczyć tablicy a nie pojedynczch liczników).
    Napisz też funkcję, która wywoła się rekurencyjnie m razy z argumentem będącym wskaźnikiem na taką tablicę (wskaźnik unique_ptr ustaw za pomocą przniesienia). W i-tym wywołaniu funkcja ta ma zwiększyć o wartość i 10% losowo wybranych elementów. */
#include <iostream>
#include <memory>
#include <ctime>
#include <cstdlib>

using namespace std;

class Counter {
public:
    Counter() : c(1) {}
    virtual ~Counter() {
        cerr << c << endl;
    }
    void increase() {
        c++;
    }
    int get_counter(){
        return c;
    }


private:
    uint64_t c;
};

void increaseRandomCounters(unique_ptr<Counter[]>& ptr, int m, int arraysize) {
    if (m == 0) {
        return;
    }


    int numElementsToIncrease = arraysize * 0.1;

    for (int i = 0; i < numElementsToIncrease; ++i) {
        int randomIndex = rand() % arraysize;
        ptr[randomIndex].increase();
    }

    increaseRandomCounters(ptr, m - 1,arraysize);
}

int main() {
    int arraysize = 20;
    unique_ptr<Counter[]> counters(new Counter[arraysize]);

    srand(static_cast<unsigned>(time(0)));

    increaseRandomCounters(counters, 20, arraysize);
    for (int i =0 ; i < arraysize; ++i){
        cout<<counters[i].get_counter()<<endl;
    }


    return 0;
}
