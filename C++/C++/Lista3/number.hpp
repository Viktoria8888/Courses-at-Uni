
#ifndef LICZBA_HPP
#define LICZBA_HPP
#include <iostream>
using namespace std;
class Liczba {
protected:
    static int MAX_HISTORIA;
private:
    
    double wartosc;
    double* historia;
    int ileHistorii;
    int indeksNowejWartosci;

public:
    Liczba();
    Liczba(double wartosc);
    Liczba(const Liczba& liczba);
    Liczba(Liczba&& liczba);
    ~Liczba();
    Liczba& operator=(const Liczba& liczba);
    Liczba& operator=(Liczba&& liczba);
    double pobierz() const;
    void ustaw(double nowaWartosc);
    void przywroc();
};

#endif