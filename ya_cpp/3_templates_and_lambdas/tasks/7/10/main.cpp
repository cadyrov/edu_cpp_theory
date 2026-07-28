//10.  Напишите `compose`, который хранит две функции и вызывает `f(g(x))`.
#include <utility>

template<typename F, typename G>
struct compose{
    F f;
    G g;

    template<typename T1>
    decltype(auto) operator()(T1&& in) {
        return f(g(std::forward<T1>(in)));
    }
};


int main() {
    auto f = [](int x) { return x + 1; };
    auto g = [](int x) { return x * 2; };

    compose c{f, g};

    int result = c(10); // f(g(10)) = 21


    return 0;
}