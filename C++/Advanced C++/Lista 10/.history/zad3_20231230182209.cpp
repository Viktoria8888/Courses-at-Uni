#include <iostream>
#include <fstream>
#include <iconv.h>
#include <vector>
#include <cstring>

bool convert_encoding(const std::string &inputFile, const std::string &outputFile, const std::string &fromEncoding, const std::string &toEncoding) {
    std::ifstream fin(inputFile, std::ios::binary);
    std::ofstream fout(outputFile, std::ios::binary);

    if (!fin || !fout) {
        std::cerr << "Cannot open file.\n";
        return false;
    }
    //c_str -> const char*
    iconv_t conv = iconv_open(toEncoding.c_str(), fromEncoding.c_str());
    if (conv == (iconv_t)-1) {
        std::cerr << "Failed to open iconv.\n";
        return false;
    }

    std::vector<char> inputBuffer(1024);
    std::vector<char> outputBuffer(4096);
    size_t inBytes, outBytes;
    char *inPtr, *outPtr;

    while (!fin.eof()) {
        fin.read(inputBuffer.data(), inputBuffer.size());
        inBytes = fin.gcount();
        inPtr = inputBuffer.data();

        while (inBytes > 0) {
            outPtr = outputBuffer.data();
            outBytes = outputBuffer.size();
            size_t result = iconv(conv, &inPtr, &inBytes, &outPtr, &outBytes);

            if (result == (size_t)-1) {
    switch (errno) {
        case EILSEQ:
            std::cerr << "Invalid multibyte sequence.\n";
            break;
        case EINVAL:
            std::cerr << "Incomplete multibyte sequence.\n";
            break;
        case E2BIG:
            std::cerr << "Output buffer is too small.\n";
            break;
        default:
            std::cerr << "Unknown conversion error.\n";
    }
    iconv_close(conv);
    return false;
}


            fout.write(outputBuffer.data(), outputBuffer.size() - outBytes);
        }
    }

    iconv_close(conv);
    return true;
}

int main() {
    std::string inputFile = "from.txt"; // Path to your UTF-8 encoded file
    std::string outputUtf32 = "output_utf32.txt";
    std::string outputIso88592 = "output_iso88592.txt";

    convert_encoding(inputFile, outputUtf32, "UTF-8", "UTF-32");
    convert_encoding(inputFile, outputIso88592, "UTF-8", "ISO-8859-2");

    return 0;
}
