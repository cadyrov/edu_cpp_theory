/*
7. Используйте `get()` для передачи сырого указателя без владения.
*/
#include <iostream>
#include <memory>

int main() {
    auto p = std::make_unique<int>(12);

    auto n = p.get();

    std::cout << *n << "\n";
}