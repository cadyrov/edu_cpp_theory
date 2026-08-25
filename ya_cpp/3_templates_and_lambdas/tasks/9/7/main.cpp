#include <iostream>

template <std::size_t N>
struct Fact {   
    static const size_t value = Fact<N-1>::value * N;
};

template <>
struct Fact<1> {   
    static const size_t value = 1;
};


int main() {
    std::cout << Fact<5>::value;
}