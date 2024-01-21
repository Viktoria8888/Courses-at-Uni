#include "number.hpp"
#include "number.cpp"

int main(){

    int s = 5;
    Liczba l1;
    
    cout<< sizeof(45ull)<<"\n";
    /*cout << "Sprawdzam konstruktor kopiujacy, kopiuję l1: ";
    Liczba l2(l1);
    cout << l2.pobierz() <<'\n';
    l2.przywroc();
    
    cout << "Sprawdzam konstruktor przenaszący, kopiuję l1: ";
    Liczba l3(std::move(l1));

    std::cout << l3.pobierz() << std::endl; 

    l3.przywroc();

    std::cout << l3.pobierz() << std::endl; */


    return 0;
}