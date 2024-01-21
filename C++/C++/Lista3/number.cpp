#include "number.hpp"
#include <cstring>

#include <stdexcept>
#include <iostream>
int Liczba::MAX_HISTORIA = 3;

Liczba::Liczba() : Liczba(0.0) {}

Liczba::Liczba(double wartosc) : wartosc(wartosc), ileHistorii(0), indeksNowejWartosci(0) {
    historia = new double[MAX_HISTORIA];
}

Liczba::Liczba(const Liczba& liczba) : wartosc(liczba.wartosc), ileHistorii(liczba.ileHistorii), 
indeksNowejWartosci(liczba.indeksNowejWartosci) {
    historia = new double[MAX_HISTORIA];
    for (int i = 0; i < liczba.ileHistorii; i++) {
        historia[i] = liczba.historia[i];
    }
    cerr << "konstruktor kopiujacy Liczba(const Liczba& liczba) [" << historia<< "]" << endl;
}

Liczba::Liczba(Liczba&& liczba) : wartosc(liczba.wartosc), historia(liczba.historia),
    ileHistorii(liczba.ileHistorii), indeksNowejWartosci(liczba.indeksNowejWartosci) {
    liczba.historia = nullptr;
    liczba.ileHistorii = 0;
    cerr << "konstruktor przenoszacy Liczba(Liczba&& liczba) [" << historia << "]" << endl;
}

Liczba::~Liczba() {
    delete[] historia;
    cerr << "desrtuktor ~Liczba() [" << historia << "]" << endl;
}

Liczba& Liczba::operator=(const Liczba& liczba) {
    if (this == &liczba) {
        throw invalid_argument("Przypisujesz ta sama liczbe");}
        
    else{
        wartosc = liczba.wartosc;
        ileHistorii = 0;
        indeksNowejWartosci = 0;
        return *this;
    }
    }
    


Liczba& Liczba::operator=(Liczba&& liczba) {
    if (this != &liczba) {
        wartosc = liczba.wartosc;
        historia = liczba.historia;
        ileHistorii = liczba.ileHistorii;
        indeksNowejWartosci = liczba.indeksNowejWartosci;
        liczba.historia = nullptr;
        liczba.ileHistorii = 0;
    }
    return *this;
}

double Liczba::pobierz() const {
    if (ileHistorii > 0) {
        return historia[indeksNowejWartosci - 1];
}
    return wartosc;
}

void Liczba::ustaw(double nowaWartosc) {
    if (ileHistorii < MAX_HISTORIA) {
        historia[indeksNowejWartosci++] = nowaWartosc;
        ileHistorii++;
    }
    else {
        historia[indeksNowejWartosci++] = nowaWartosc;
        indeksNowejWartosci %= MAX_HISTORIA;}} //zawinięcie w tablic

 void Liczba::przywroc() {
        if (ileHistorii > 0) {
            wartosc = historia[indeksNowejWartosci - 1];
            indeksNowejWartosci--;
            indeksNowejWartosci %= MAX_HISTORIA;
            ileHistorii--;
        }
    }