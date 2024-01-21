#include <iostream>
#include <cstdint>
enum class Names : std::uint16_t
{
    Kasia = 10,
    Basia = 11,
    Franek = 12,
    Antoni = 13

};
void message_for(std::string& m, Names name){
    switch (name)
    {
        case Names::Kasia:
            std::cout << "Dla Kasi: " << m << std::endl;
            break;
        case Names::Basia:
            std::cout << "Dla Basi: " << m << std::endl;
            break;
        case Names::Franek:
            std::cout << "Dla Franka: " << m << std::endl;
            break;
        case Names::Antoni:
            std::cout << "Dla Antoniego: " << m << std::endl;
            break;
        default:
            break;
    }
}
int main()
{
    std::string m = "Hejka, jak leci?";
    Names name = Names::Antoni;

    message_for(m, name);

    return 0;
}
