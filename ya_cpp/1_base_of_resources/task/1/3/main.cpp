// 3. Напишите функцию, которая создает строку через `new std::string` и возвращает сырой указатель.
#include <iostream>
#include <string>

std::string* new_string() {
    return new std::string("test");
}

int main() {
    auto s = new_string();

    std::cout << s << "\n";
    std::cout << *s << "\n";

    return 0;
}

// clang++ --std=c++23 -o main