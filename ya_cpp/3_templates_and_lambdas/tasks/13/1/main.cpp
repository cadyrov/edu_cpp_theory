//  Напишите generic lambda `identity`.
#include <iostream>

int main() {
    auto identity = [](auto x) { return x; };

    std::cout << identity(1) << " " << identity(1.0f) << "\n";

    return 0;
}

// clang++ --std=c++23 -o main