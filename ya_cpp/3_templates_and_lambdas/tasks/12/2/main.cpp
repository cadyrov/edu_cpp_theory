#include <iostream>

int main() {
    int limit = 100;

    auto f = [limit](int x) { return x < limit; };

    std::cout << std::boolalpha;
    std::cout << f(10) << "\n";
    std::cout << f(101) << "\n";

    return 0;
}