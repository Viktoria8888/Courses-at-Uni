#include <iostream>
// decltype(auto) is used here to delay the return type deduction
decltype(auto) lucas_numbers(std::uint64_t n){
    if (n == 0){
        return 2;
    }
    if (n == 1){
        return 1;
    }
    return lucas_numbers(n-1) + lucas_numbers(n-2);
}

int main() {
    std::cout<<lucas_numbers(7)<<std::endl;
    return 0;
}
