#include <iostream>

int main() {

    std::string adresInstytutu = R"(
    Instytut Informatyki
    Fryderyka Joliot-Curie 15
    50-383 Wrocław)";
    std::string sciezkaWindows = R"(C:\Program Files\User\Cpp\CośTam)";

    // Surowy łańcuch znaków (raw string) z różnymi sekwencjami znaków specjalnych
    std::string sekwencjeSpecjalne = R"( " ") ("  )";

    // Wypisywanie na standardowe wyjście
    std::cout << "Adres Instytutu:\n" << adresInstytutu << "\n\n";
    std::cout << "Ścieżka bezwzględna w systemie Windows:\n" << sciezkaWindows << "\n\n";
    std::cout << "Różne sekwencje znaków cudzysłowia i nawiasów okrągłych:\n" << sekwencjeSpecjalne << "\n\n";

    return 0;
}

