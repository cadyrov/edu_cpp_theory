/*
9. Используйте `release()` и вручную освободите полученный сырой указатель.
*/
#include <iostream>
#include <memory>

int main() {
    auto p = std::make_unique<int>(12);

    auto x = p.release();

    std::cout << *x << "\n";

    delete x;
}