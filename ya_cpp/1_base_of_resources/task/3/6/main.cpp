/*
6. Напишите функцию, которая возвращает `std::unique_ptr<T>`.
*/
#include <iostream>
#include <memory>

std::unique_ptr<int> process(int x) {
    return std::make_unique<int>(x);
}

int main() {
    std::cout << *process(12) << "\n";
}