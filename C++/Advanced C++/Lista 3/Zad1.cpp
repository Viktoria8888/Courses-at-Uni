#include <iostream>
#include <limits>

int main() {
    std::cout << "Najmniejsza wartość long long int: " << std::numeric_limits<long long int>::min() << std::endl;
    std::cout << "Największa wartość long long int: " << std::numeric_limits<long long int>::max() << std::endl;
    std::cout<<std::numeric_limits<long long int>::digits<<std::endl;
    return 0;
}


/*Wypisz najmniejszą i największą wartość jaką można zapisać w typie long long int. Na ilu bitach jest ta liczba zapisywana i ile to będzie cyfr dziesiętnych? */
