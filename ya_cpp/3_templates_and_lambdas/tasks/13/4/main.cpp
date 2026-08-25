//  4. Напишите лямбду `forward_to`, которая идеально передает callable и аргумент.
#include <iostream>
#include <utility>

int main() {
    auto forward_to = []<typename F, typename... Args>(F&& fn, Args&&... args) -> decltype(auto) {
        return std::forward<F>(fn)(std::forward<Args>(args)...);
    };

    return 0;
}

// clang++ --std=c++23 -o main