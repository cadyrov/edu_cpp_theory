// Напишите функцию `is_even`, доступную только для integral-типов через `std::enable_if_t`.
#include <iostream>
#include <type_traits>

template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0> bool is_even(T in) {
    return in % 2 == 0;
}

int main() {
    std::cout << is_even(3) << "\n";

    return 0;
}

// clang++ --std=c++23 -o main