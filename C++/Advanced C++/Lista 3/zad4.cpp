#include <iostream>
#include <type_traits>
#include <string>


template <typename From, typename To>
void moveFromTo(From& from, To& to)
{
    if constexpr (std::is_convertible<From, To>::value)
    {
        to = static_cast<To&&>(std::move(from));


        std::cout << "Used no pointer version." << std::endl;
    }
    else
        std::cout << "Failed to convert." << std::endl;
}


int main()
{

    std::string str1 = "first string";
    std::string str2 = "second string";

    moveFromTo(str1, str2);
    std::cout << str2 << std::endl;
}
