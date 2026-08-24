//  3. Напишите variadic generic lambda `print_all`, раскрывающую пакет через fold expression.
#include <iostream>

int main() {
    auto print_all = []<typename... Args>(Args&&... args) { ((std::cout << args << " "), ...); };

    print_all(1, "cdsc", 3, 4, 5);

    return 0;
}

// clang++ --std=c++23 -o main