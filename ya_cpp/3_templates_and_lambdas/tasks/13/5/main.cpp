// Напишите функцию `make_printer`, возвращающую лямбду с захватом пакета `[args...]`.
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