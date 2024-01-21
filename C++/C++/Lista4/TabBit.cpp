#include "TabBit.hpp"


const int tab_bit::rozmiarSlowa = 64;


// Ref class

tab_bit::ref::ref(const tab_bit &tb, int ind) : tb(tb), ind(ind) {}

tab_bit::ref::operator bool() const {
    //знаходить відділ в таблиці, де знаходиться н-ти індекс, того
    // біта, який шукаємо
    slowo l = tb.tab[ind / rozmiarSlowa];
    // знаходить конкретно тей біт який шукаємо,
    // в тій комурці памяті, яка зараз називається l

    //shifting the word, so that the bit we are interested in
    //is on the least significant place (start indexing from the right)
    l>>=(ind % rozmiarSlowa);

    // returns the least significant bit in l using "bit masking"
    return (bool)(l&1);
}

//the function would return the REFERENCE to an existing object,
// so that's why I' am using & here
tab_bit::ref& tab_bit::ref::operator=(bool b) {
    int komorka_pamieci = ind / rozmiarSlowa; // the word in tab that contains the desired bit
    int przesuniecie_bitowe = ind % rozmiarSlowa;
    if (b) {
        // setting bit to 1
        // First shift the bits of binary representation of 1 (with 64 bits)
        // then use OR operator
        tb.tab[komorka_pamieci] |= (1ULL << przesuniecie_bitowe);
    } else {
        // setting bit to 0
        // First shift the bits of binary representation of 1 (with 64 bits)
        // then use NOT operator and AND operator
        
        tb.tab[komorka_pamieci] &= ~(1ULL << przesuniecie_bitowe);
    }
    return *this;
}


tab_bit::ref &tab_bit::ref::operator=(const ref &r) {
    bool b = bool(r);
    *this = b; 
    return *this;
}
//


tab_bit::tab_bit(int rozm): dl(rozm)
{
    if (rozm< 0){
        throw std::invalid_argument("Rozmiar nie moze byc ujemny");
    }
    // calculating how many words ot would take to store those bits
    int new_rozm = (rozm + rozmiarSlowa -1)/rozmiarSlowa;
    
    tab = new slowo[new_rozm];
    for (int i = 0; i < new_rozm; ++i)
        tab[i]=0;
}

tab_bit::tab_bit(slowo tb){
    int new_rozm = sizeof(slowo)*8; // 64
    //because tb is going to require at most 64 bits

    tab = new slowo[1];
    tab[0] = tb;

}

tab_bit::tab_bit(initializer_list<bool> list) {
    int rozmiar = list.size();
    dl = rozmiar;
    tab = new slowo[(rozmiar + rozmiarSlowa - 1) / rozmiarSlowa];

    int i = 0;
    
    for (auto iterator = list.begin(); iterator != list.end(); iterator++) {
        this->operator[](i) = *iterator;
        i++;
    }
}

// Copy constructor
tab_bit::tab_bit (const tab_bit &tb) {
    dl = tb.dl;
    int rozm = (dl + rozmiarSlowa - 1) / rozmiarSlowa;
    tab = new slowo[rozm];
    memcpy(tab,tb.tab,rozm*sizeof(slowo));
    
}

tab_bit::tab_bit (tab_bit &&tb) : dl(0), tab(nullptr) {
    std::swap(this->dl, tb.dl);
    std::swap(this->tab, tb.tab);
    
}






tab_bit::~tab_bit(){
    delete[] tab;
}

// Operators =

tab_bit& tab_bit::operator=(const tab_bit& tb) {
    if (this == &tb) return *this;
    delete[] tab; // clear the current tab
    dl = tb.dl; // set the length
    int new_rozm = (dl + rozmiarSlowa - 1) / rozmiarSlowa;
    tab = new slowo[new_rozm];
    copy(tb.tab, tb.tab + new_rozm, tab);
    return *this;
}


tab_bit & tab_bit::operator = (tab_bit &&tb) {
    if (this == &tb) return *this;
    std::swap(dl, tb.dl);
    std::swap(tab, tb.tab);
    return *this;
}
bool tab_bit::operator[] (int i) const {
    return bool(ref(*this, i));
}

tab_bit::ref tab_bit::operator[] (int i) {
    return ref(*this, i);
}

int tab_bit::rozmiar () const {
    return dl;
}

// Streams

bool tab_bit::czytaj (int i) const {
    if (i < 0 || i >= dl)
        throw std::invalid_argument(std::string("Indeks jest spoza tablica"));
    ref r(*this, i);
    return bool(r);
}

void tab_bit::pisz (int i, bool b) {
    if (i < 0 || i >= dl)
        throw std::invalid_argument(std::string("Indeks jest poza tablica"));
    ref r(*this, i);
    r = b;

}




// operatory << i >>

ostream & operator << (std::ostream &wy, const tab_bit &tb)
{
    for (int i = 0; i < tb.dl; i++) {
        wy << (tb.czytaj(i) ? '1' : '0');
    }
    return wy;
}

istream & operator >> (std::istream &we, tab_bit &tb)
{

    string input;
    we >> input;
    
    if(input.length() != tb.dl)
    {
        throw invalid_argument("Dlugosc wprowadzonych bitow sie nie zgadza");
    }
    
    for(int i=0; i<tb.dl; i++)
    {
        if(input[i] == '0')
        {
            tb[i] = false;
        }
        else if(input[i] == '1')
        {
            tb[i] = true;
        }
        else
        {
            throw invalid_argument("Podaj 0 lub 1");
        }
    }
    
    return we;
}

// Bitwise operations

tab_bit tab_bit::operator|(const tab_bit& b){
    int nowy_rozmiar = max(this->rozmiar(), b.dl);
    int itr = min(this->rozmiar(), b.dl);

    tab_bit wynik(nowy_rozmiar);
    if (dl > b.dl) {
        wynik = *this;
    }
    else {
        wynik = b;
    }
    for (int i=0; i<itr; ++i){
        wynik[i] = bool(b[i]) || bool(this->operator[](i));
    }
    return wynik;
}

tab_bit& tab_bit::operator|=(const tab_bit& b){
    int nowy_rozmiar = max(this->rozmiar(), b.dl);
    int itr = min(this->rozmiar(), b.dl);

    tab_bit wynik(nowy_rozmiar);

    for (int i=0; i<itr; ++i){
        wynik[i] = bool(b[i]) || bool(this->operator[](i));
    }
    *this = wynik;
    return *this;
}

tab_bit tab_bit::operator & (const tab_bit& b) {
    int nowy_rozmiar = max(this->rozmiar(), b.dl);
    int itr = min(this->rozmiar(), b.dl);

    tab_bit wynik(nowy_rozmiar);

    for (int i=0; i<itr; ++i){
        wynik[i] = bool(b[i]) && bool(this->operator[](i));
    }
    return wynik;
}

tab_bit& tab_bit::operator &= (const tab_bit& b) {
    int nowy_rozmiar = max(this->rozmiar(), b.dl);
    int itr = min(this->rozmiar(), b.dl);

    tab_bit wynik(nowy_rozmiar);

    for (int i=0; i<itr; ++i){
        wynik[i] = bool(b[i]) && bool(this->operator[](i));
    }
    *this = wynik;
    return *this;
}

 tab_bit tab_bit::operator^(const tab_bit& b){
    int nowy_rozmiar = max(this->rozmiar(), b.dl);
    int itr = min(this->rozmiar(), b.dl);

    tab_bit wynik(nowy_rozmiar);

    for (int i=0; i< itr; ++i){
        wynik[i] = bool(b[i])^ bool(this->operator[](i));
    }
    return wynik;

}

tab_bit& tab_bit::operator^=(const tab_bit& b){
    int nowy_rozmiar = max(this->rozmiar(), b.dl);
    int itr = min(this->rozmiar(), b.dl);

    tab_bit wynik(nowy_rozmiar);

    for (int i=0; i< itr; ++i){
        wynik[i] = bool(b[i])^ bool(this->operator[](i));
    }
    *this = wynik;
    return *this;

}


tab_bit tab_bit::operator ! (){
    for (int i=0; i< this->rozmiar(); ++i){
        this->operator[](i) = !(bool(this->operator[](i)));
    }
    return *this;
}













