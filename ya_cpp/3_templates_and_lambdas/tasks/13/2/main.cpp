//  Напишите шаблонную лямбду `cast_to<T>` и вызовите ее через `operator()<T>`.
#include <iostream>

int main() {
    auto cast_to = []<typename T>(auto x) { return static_cast<T>(x); };

    std::cout << cast_to.operator()<float>(3) << "\n";

    return 0;
}

// clang++ --std=c++23 -o main