#include <iostream>
#include <complex>
#include <cmath>

const double eulerGamma = 0.5772156649;



std::complex<double> gamma(const std::complex<double>& z, int iterations) {
    std::complex<double> result = 1.0 / z;

    for (int n = 1; n < iterations; ++n) {
        double dn = static_cast<double>(n);
        result *= std::pow((1.0 + 1.0 / dn), z) / (1.0 + z / dn);
    }

    return result;
}

std::complex<double> inverseGamma(std::complex<double>& z, int iterations) {
    std::complex<double> result = z * std::exp(eulerGamma * z);

    std::complex<double> term = 1;

    for (int n = 1; n < iterations; ++n) {
        double dn = static_cast<double>(n);
        term *= (1.0 + z / dn) * std::exp(-z / dn);

    }

    return result*term;
}

int main() {

    std::complex<double> z1(2.0, 3.0);
    std::complex<double> z2(1.5, -1.0);

    int iterations = 1050;

    std::cout << "Gamma" << z1 << " = " << gamma(z1, iterations) << std::endl;
    std::complex<double> z(2.0, 3.0);

    std::cout << "Inverse Gamma" << z2 << " = " << gamma(z2, iterations) * inverseGamma(z2, iterations) << std::endl;

    return 0;
}
