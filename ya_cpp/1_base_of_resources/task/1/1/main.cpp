// Выделите `int` через `new`, запишите значение и освободите через `delete`.
#include <iostream>

int main() {
    int* x = new int(33);

    std::cout << x << "\n";
    std::cout << *x << "\n";

    delete x;

    return 0;
}

// clang++ --std=c++23 -o main