#include <iostream>
#include <algorithm>

void generatePermutations(std::string str)
{

    std::sort(str.begin(), str.end());

    do
    {
        std::cout << str << std::endl;
    } while (std::next_permutation(str.begin(), str.end()));
}

int main()
{
    std::string input;
    std::cout << "Enter a string: ";
    std::cin >> input;

    generatePermutations(input);

    return 0;
}
