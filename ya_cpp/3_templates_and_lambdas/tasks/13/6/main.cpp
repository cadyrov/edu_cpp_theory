// 6. Используйте `std::bind_front`, чтобы зафиксировать первый аргумент функции логирования.
#include <iostream>
#include <utility>

template <typename... Args> auto make_printer(Args&&... args) {
    return [... args = std::forward<Args>(args)] { ((std::cout << args), ...); };
}

int main() {
    auto printer = make_printer(1, " ", 2, " ");

    printer();
}

// clang++ --std=c++23 -o main