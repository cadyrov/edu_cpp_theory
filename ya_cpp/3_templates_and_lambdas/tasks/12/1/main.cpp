#include <iostream>

int main() {
    auto f = [](int x) { return x * x; };

    std::cout << f(10) << "\n";

    return 0;
}