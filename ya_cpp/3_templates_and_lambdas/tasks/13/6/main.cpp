// 6. Используйте `std::bind_front`, чтобы зафиксировать первый аргумент функции логирования.
#include <functional>
#include <iostream>
#include <string>
#include <utility>

template <typename... Args> void log(Args&&... args) {
    ((std::cout << std::forward<Args>(args)), ...);
}

int main() {
    auto log_main = std::bind_front(
        [](auto&&... args) { log(std::forward<decltype(args)>(args)...); }, "main_log: ");

    log_main(1, " ", 2, " ");
}

// clang++ --std=c++23 -o main