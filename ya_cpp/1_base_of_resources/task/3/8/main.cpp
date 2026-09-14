/*
8. Используйте `reset()` для замены объекта.
*/
#include <iostream>
#include <memory>

int main() {
    auto p = std::make_unique<int>(12);

    int m = 5;

    p.reset(&m);

    std::cout << *p << "\n";
}