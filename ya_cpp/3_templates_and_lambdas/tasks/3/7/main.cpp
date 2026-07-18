#include <iostream>
#include <print>

template<typename T>
constexpr T pi = T(3.1415926535);


int main() {
    std::println("float {}, double {}", pi<float>, pi<double>);

    return 0;
}