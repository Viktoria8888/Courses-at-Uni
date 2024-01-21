#include <iostream>


template<size_t N>
double inner(double *x, double *y) {
    return x[N-1] * y[N-1] + inner<N-1>(x, y);
}


template<>
double inner<0>(double *x, double *y) {
    return 0;
}

int main() {
    double x[] = {1, 2, 3};
    double y[] = {4, 5, 6};
    std::cout <<inner<3>(x, y) << std::endl;
    return 0;
}
