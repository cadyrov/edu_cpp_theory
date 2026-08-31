// Выделите массив `int` через `new[]`, заполните и освободите через `delete[]`.
#include <iostream>

int main() {
    int* x = new int[4];

    x[0] = 5;
    x[1] = 6;
    x[2] = 7;
    x[3] = 8;

    for (size_t i = 0; i < 4; ++i) {
        std::cout << x[i] << "\n";
    }

    delete[] x;

    return 0;
}

// clang++ --std=c++23 -o main