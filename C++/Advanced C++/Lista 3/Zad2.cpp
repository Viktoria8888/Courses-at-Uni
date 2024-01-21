
/*Jaka jest najbliższa 0 liczba dodatnia dla typów float i double? Jakie są maksymalne wartości zapisywane w tych typach? Jaka jest różnica pomiędzy 1 a najmniejszą liczbą >1 w tych typach?*/

#include <iostream>

#include <limits>
int main() {
    std::cout << "Najbliższa 0 dodatnia liczba dla typu float: " << std::numeric_limits<float>::denorm_min() << std::endl;
    std::cout << "Najbliższa 0 dodatnia liczba dla typu double: " << std::scientific << std::numeric_limits<double>::denorm_min()<< std::endl;


    std::cout << "Największa wartość dla typu float: " << std::numeric_limits<float>::max() << std::endl;
    std::cout << "Największa wartość dla typu double: " << std::numeric_limits<double>::max() << std::endl;

    // Najmniejszy przyrost, który można dodać, żeby uzyskać róźną liczbę od 1
    float epsilonFloat = std::numeric_limits<float>::epsilon();
    double epsilonDouble = std::numeric_limits<double>::epsilon();

    std::cout << "Epsilon maszynowy dla typu float: " << epsilonFloat << std::endl;
    std::cout << "Epsilon maszynowy dla typu double: " << epsilonDouble << std::endl;

    return 0;
    return 0;
}
