//3. Напишите функцию `repeat<N>`, которая печатает строку `N` раз.

#include <print>
#include <cstddef>
#include <string>

template<std::size_t N>
void repeat(const std::string& in) {
    for (std::size_t i = 0; i < N; ++i) {
        std::println("{}",in);
    }
}

int main() {
    repeat<5>("hello");

    return 0;
}