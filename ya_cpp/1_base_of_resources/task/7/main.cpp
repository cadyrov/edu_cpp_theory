// 7. Напишите пример неправильной пары `new[]` и `delete`.
#include <iostream>

int main() {
    int* p = new int[4];

    delete p;
}

// clang++ --std=c++23 -o main