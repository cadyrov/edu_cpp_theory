#include <iostream>

template <typename... Args> auto sum_all(Args... args) {
    return (args + ... + 0);
}

int main() {
    std::cout << sum_all() << std::endl;

    std::cout << sum_all(1, 2, 3, 4, 5.0) << std::endl;

    std::cout << sum_all(1, 2, 3, 4, 5.0) << std::endl;

    return 0;
}