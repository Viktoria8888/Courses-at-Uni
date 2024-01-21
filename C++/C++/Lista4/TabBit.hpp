#include <iostream>
#include <stdexcept>
#include <cstring>
using namespace std;
class tab_bit
{
    typedef uint64_t slowo;        // komorka w tablicy
    static const int rozmiarSlowa; // rozmiar slowa w bitach
    friend istream &operator>>(istream &we, tab_bit &tb);
    friend ostream &operator<<(ostream &wy, const tab_bit &tb);
     // klasa pomocnicza do adresowania bitów
     class ref
    {
    protected:
        friend class tab_bit;
        const tab_bit &tb;
        int ind;
        
    public:
        ref(const tab_bit &tb, int ind);
        operator bool() const;
        ref &operator=(bool b);
        ref &operator=(const ref &r);
    };

protected:
    int dl;     // liczba bitów
    slowo *tab; // tablica bitów

public:
    tab_bit() : dl(0), tab(nullptr) {}

    explicit tab_bit(int rozm); // wyzerowana tablica bitow [0...rozm]
    explicit tab_bit(slowo tb); // tablica bitów [0...rozmiarSlowa]

    tab_bit (std::initializer_list<bool> lista); // zainicjalizowana wzorcem
    tab_bit(const tab_bit &tb);            // konstruktor kopiujący
    tab_bit(tab_bit &&tb);                 // konstruktor przenoszący
    tab_bit &operator=(const tab_bit &tb); // przypisanie kopiujące
    tab_bit &operator=(tab_bit &&tb);      // przypisanie przenoszące
    ~tab_bit();                            // destruktor
    

private:
    bool czytaj(int i) const; // metoda pomocnicza do odczytu bitu
    void pisz(int i, bool b); // metoda pomocnicza do zapisu bitu
public:
    bool operator[](int i) const; // indeksowanie dla stałych tablic bitowych
    ref operator[](int i);        // indeksowanie dla zwykłych tablic bitowych
    inline int rozmiar() const;   // rozmiar tablicy w bitach
public:
    // operatory bitowe: | i |=, & i &=, ^ i ^= oraz !
    tab_bit operator|(const tab_bit& b);
    tab_bit& operator|=(const tab_bit& b);
    tab_bit operator&(const tab_bit& b);
    tab_bit& operator&=(const tab_bit& b);
    tab_bit operator^(const tab_bit& b);
    tab_bit& operator^=(const tab_bit& b);
    tab_bit operator ! ();
public:
    // zaprzyjaźnione operatory strumieniowe: << i >>
};