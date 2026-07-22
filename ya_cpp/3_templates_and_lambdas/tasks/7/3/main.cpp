//3. Напишите функцию `forward_to`, которая передает аргумент в другую функцию через `std::forward`.
#include <cassert>
#include <cmath>
#include <type_traits>
#include <utility>

template <typename T>
void pass(T&&) {
  if constexpr (std::is_lvalue_reference_v<T>) {
        static_assert(std::is_same_v<T, int&>);
    } else {
        static_assert(std::is_same_v<T, int>);
    }
}

template <typename T, void (*Callback)(T)>
void forward_to(T&& in) {
    Callback(std::forward<T>(in));
}

int main() {
    int a =9;
    pass(a);
    pass(4);

    forward_to<int&, pass<int&>>(a);

    return 0;
}