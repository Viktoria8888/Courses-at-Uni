#include <iostream>


template<size_t N>
double inner(double *x, double *y) {
    return x[N-1] * y[N-1] + inner<N-1>(x, y);
}


template<>
double inner<0>(double *x, double *y) {
    return 0;
}

template<size_t N, typename T = double>
T inner(T *x, T *y){
    if constexpr (N==0){return 0;}
    return x[N-1] * y[N-1] + inner<N-1>(x, y);
}
// template<typename T>
// T inner<0>(T *x, T *y) {
//     return 0;
// }
int main() {
    int x[] = {1, 2, 3};
    int y[] = {4, 5, 6};
    std::cout <<inner<3,int>(x, y) << std::endl;
    return 0;
}
