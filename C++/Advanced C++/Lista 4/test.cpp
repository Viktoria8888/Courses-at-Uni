#include <iostream>
#include <string>

// Function template for the neutral element of addition
template <typename T>
T neutral_element_addition() {
    return T(0);
}

// Function template for the neutral element of multiplication
template <typename T>
T neutral_element_multiplication() {
    return T(1);
}

int main() {
    int neutral_add = neutral_element_addition<int>();
    float neutral_mult = neutral_element_multiplication<float>();
    std::string neutral_str = neutral_element_addition<std::string>();

    std::cout << "Neutral element for addition (int): " << neutral_add << std::endl;
    std::cout << "Neutral element for multiplication (float): " << neutral_mult << std::endl;
    std::cout << "Neutral element for addition (string): " << neutral_str << std::endl;

    return 0;
}
