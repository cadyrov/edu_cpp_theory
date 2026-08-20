// 9. Напишите функцию, возвращающую лямбду-предикат, и не допускайте висячей ссылки.

#include <algorithm>
#include <cassert>
#include <iostream>

auto lambda() {
    return [limit = 100](int x) { return x > limit; };
}

int main() {
    auto ld = lambda();

    ld(12);

    return 0;
}