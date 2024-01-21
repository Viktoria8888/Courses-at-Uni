#include <iostream>
#include <fstream>
#include <random>

int main()
{
    // Ustawienia dla generatora liczb pseudolosowych
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generowanie liczb z rozkładem jednostajnym
    std::uniform_real_distribution<double> uniformDist(0.0, 1.0);
    std::ofstream uniformFile("uniform_distribution.csv");
    for (int i = 0; i < 1000; ++i)
    {
        uniformFile << uniformDist(gen) << "\n";
    }
    uniformFile.close();

    // Generowanie liczb z rozkładem dwumianowym
    std::binomial_distribution<int> binomialDist(10, 0.5);
    std::ofstream binomialFile("binomial_distribution.csv");
    for (int i = 0; i < 1000; ++i)
    {
        binomialFile << binomialDist(gen) << "\n";
    }
    binomialFile.close();

    // Generowanie liczb z rozkładem normalnym
    std::normal_distribution<double> normalDist(0.0, 1.0);
    std::ofstream normalFile("normal_distribution.csv");
    for (int i = 0; i < 1000; ++i)
    {
        normalFile << normalDist(gen) << "\n";
    }
    normalFile.close();

    return 0;
}
