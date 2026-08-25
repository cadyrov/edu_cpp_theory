#include <iostream>

template<size_t N>
struct Sum{
    static const unsigned val = Sum<N-1>::val + N;
};

template<>
struct Sum<1>{
    static const unsigned val = 1;
};

int main() {
    std::cout << Sum<453>::val;
    return 0;
}