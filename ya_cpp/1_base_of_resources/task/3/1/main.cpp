/*
1. Создайте `std::unique_ptr<int>` через `std::make_unique`.
*/
#include <iostream>
#include <memory>

int main() {
    auto p = std::make_unique<int>(12);

    std::cout << *p << "\n";
}