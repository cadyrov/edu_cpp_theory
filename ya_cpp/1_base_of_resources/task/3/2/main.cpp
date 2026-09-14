/*
2. Проверьте, что `unique_ptr` нельзя скопировать.
*/
#include <iostream>
#include <memory>

int main() {
    auto p = std::make_unique<int>(12);

    auto x = p;

    std::cout << *p << "\n";
}