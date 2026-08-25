// Напишите рекурсивную лямбду для вычисления `fib`: сначала через `self`, затем вариантом C++23 с
// `this auto`.
#include <iostream>

int main() {
    auto fib_impl = [](auto& self, int n) -> int {
        return n <= 1 ? n : self(self, n - 1) + self(self, n - 2);
    };

    auto fib = [fib_impl](int n) -> int { return fib_impl(fib_impl, n); };

    std::cout << fib(9) << "\n";

    auto fb = [](this auto& self, int n) -> int { return n <= 1 ? n : self(n - 1) + self(n - 2); };
    std::cout << fb(9) << "\n";
}

// clang++ --std=c++23 -o main