#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <cmath>

std::complex<double> gamma(const std::complex<double> &z, int iterations)
{
    std::complex<double> result = 1.0 / z;

    for (int n = 1; n < iterations; ++n)
    {
        double dn = static_cast<double>(n);
        result *= std::pow((1.0 + 1.0 / dn), z) / (1.0 + z / dn);
    }

    return result;
}


std::complex<double> riemann_zeta(const std::complex<double> &z, int iterations)
{

    if (iterations == 0)
        return 0.0;

    return std::pow(2.0, z) * std::pow(M_PI, z - 1.0) * std::sin(M_PI * z / 2.0) * gamma(1.0 - z, 1000);
}

int main()
{
    const int num_points = 500;
    const double step = 0.01;
    const double critical_line_real = 0.5;

    std::ofstream outfile("riemann_zeta_values.csv");



    std::vector<double> real_values;
    std::vector<double> imag_values;

    for (int i = -30; i < 30 ; ++i)
    {
        double t = i;
        std::complex<double> z(critical_line_real, t);
        std::complex<double> zeta_value = riemann_zeta(z, 1000); // Adjust the number of iterations as needed

        // Output to CSV file
        outfile << zeta_value.real() << "," << zeta_value.imag() << "\n";

        // Store values for plotting
        real_values.push_back(zeta_value.real());
        imag_values.push_back(zeta_value.imag());
    }

    outfile.close();

    // Now, you can import the CSV file into a spreadsheet program (e.g., Excel or Google Sheets) and create a double plot.

    return 0;
}
