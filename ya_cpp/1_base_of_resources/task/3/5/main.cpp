/*
5. Напишите функцию, которая принимает `std::unique_ptr<T>` по значению.
*/
#include <iostream>
#include <memory>

void process(std::unique_ptr<int> x) {
    std::cout << *x << "\n";
}

int main() {
    auto p = std::make_unique<int>(12);

    process(std::move(p));
}