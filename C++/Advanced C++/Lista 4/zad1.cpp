
/*Zaimplementuj funktor compose_f_gx_hx realizujący złożenie dwuargumentowe f(g(x), h(x)). Podaj przykład jego użycia*/
#include <iostream>
#include <functional>
using namespace std;


template <typename F, typename G, typename H>
class compose_f_gx_hx {
public:
    compose_f_gx_hx(F f, G g, H h) : f(f), g(g), h(h) {}

    template <typename Arg>
    auto operator()(Arg x){
        return f(g(x), h(x));
    }

private:
    F f;
    G g;
    H h;
};

int main() {
    auto g = [](int x) { return x * 2; };
    auto h = [](int x) { return x + 3; };

    auto f = [](int a, int b) { return a + b; };

    compose_f_gx_hx<decltype(f), decltype(g), decltype(h)> composed_func(f, g, h);

    int x = 5;
    int result = composed_func(x);

    std::cout << "Result for x = " << x << " is " << result << std::endl;

    return 0;
}
