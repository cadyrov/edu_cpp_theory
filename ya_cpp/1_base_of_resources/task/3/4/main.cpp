/*
4. Проверьте состояние исходного `unique_ptr` после move.
*/
#include <iostream>
#include <memory>

int main() {
    auto p = std::make_unique<int>(12);

    auto b = std::move(p);

    std::cout << p << "\n";
}