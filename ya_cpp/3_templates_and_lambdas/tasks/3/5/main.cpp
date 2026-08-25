#include <utility>

template<typename T, typename U>
class Pair{
    public:
        template<typename T1, typename U1>
        explicit Pair(T1&& t, U1&& u):t_(std::forward<T1>(t)),u_(std::forward<U1>(u)){}
    private:
        T t_;
        U u_;
};


int main() {
    Pair<int, double> p(1, 2.);

    return 0;
}