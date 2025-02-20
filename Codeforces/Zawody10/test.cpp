#include <iostream>
#include <string>
#include <bitset> 
using namespace std;
int main() {
    // Convert binary strings to integers
    int num1 = stoi("0011", nullptr, 2); // 3 in decimal
    int num2 = stoi("0110", nullptr, 2); // 6 in decimal

    // Perform NAND: NOT (num1 AND num2)
    int nand_result = ~(num1 & num2);

    // Convert result back to binary (assuming a 32-bit integer)
    std::string binary_result = std::bitset<32>(nand_result).to_string();

    // Output the binary string
    std::cout << "Binary Result: " << binary_result << std::endl;

    return 0;
}
