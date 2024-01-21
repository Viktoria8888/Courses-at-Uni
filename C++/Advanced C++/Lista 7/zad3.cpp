#include <iostream>
#include <fstream>
#include <random>
#include <vector>


std::string generateRandomText(int textLength, const std::vector<double>& letterDistribution, std::mt19937& gen) {
    std::string result;
    std::binomial_distribution<int> wordLengthDistribution(12, 0.5);
    while (result.length() < static_cast<size_t>(textLength)) {

        int wordLength = std::min(1 + wordLengthDistribution(gen), 12);


        for (int i = 0; i < wordLength; ++i) {

            std::discrete_distribution<int> letterDist(letterDistribution.begin(), letterDistribution.end());
            result += static_cast<char>('a' + letterDist(gen));
        }


        if (result.length() < static_cast<size_t>(textLength)) {
            result += ' ';
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <text_length> <output_file_name>" << std::endl;
        return 1;
    }

    int textLength = std::stoi(argv[1]);
    std::string outputFileName = argv[2];


    std::random_device rd;
    std::mt19937 gen(rd());


    std::vector<double> letterDistribution = {0.0817, 0.0149, 0.0271, 0.0432, 0.1202, 0.0230, 0.0203, 0.0592, 0.0731, 0.0010,
                                             0.0069, 0.0398, 0.0261, 0.0681, 0.0770, 0.0166, 0.0009, 0.0568, 0.0611, 0.0937,
                                             0.0285, 0.0110, 0.0205, 0.0006, 0.0169, 0.0007};


    std::string randomText = generateRandomText(textLength, letterDistribution, gen);


    std::ofstream outputFile(outputFileName);
    if (outputFile.is_open()) {
        outputFile << randomText;
        outputFile.close();
        std::cout << "Random text generated and saved to " << outputFileName << std::endl;
    }
    return 0;
}
