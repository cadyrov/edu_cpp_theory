#include <iostream>

int main() {
    int counter = 0;

    auto f = [&counter]() { ++counter; };

    f();

    std::cout << counter << "\n";
    f();
    f();
    f();

    std::cout << counter << "\n";

    return 0;
}