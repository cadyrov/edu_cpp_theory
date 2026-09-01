// 4. Исправьте вызов этой функции так, чтобы память точно освобождалась.
#include <iostream>
#include <string>

std::string* new_string() {
    return new std::string("test");
}

int main() {
    auto s = new_string();

    std::cout << s << "\n";
    std::cout << *s << "\n";

    delete s;

    return 0;
}

// clang++ --std=c++23 -o main