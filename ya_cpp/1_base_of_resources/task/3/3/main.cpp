/*
3. Передайте владение другому `unique_ptr` через `std::move`.
*/
#include <iostream>
#include <memory>

int main() {
    auto p = std::make_unique<int>(12);

    auto b = std::move(p);

    std::cout << *b << "\n";
}