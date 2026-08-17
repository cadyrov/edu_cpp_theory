#include <type_traits>
#include <iostream>

template<typename T>
void process(T in) {
    if constexpr (std::is_integral<T>{}) {
        std::cout << 1;
    } else {
        std::cout << 55;
    }
    
}


int main() {
    process(1);
    process(2.0f);
}