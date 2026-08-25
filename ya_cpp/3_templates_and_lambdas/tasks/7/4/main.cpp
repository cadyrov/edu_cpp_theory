//4. Покажите разницу между `std::move` и `std::forward`.
#include <cstddef>
#include <string>
#include <utility>
#include <print>

template <typename T>
void pass(T&&) {
  if constexpr (std::is_lvalue_reference_v<T>) {
        static_assert(std::is_same_v<T, int&>);
    } else {
        static_assert(std::is_same_v<T, int>);
    }
}

template <typename T>
void pass_mv(T&& in) {
    pass(std::move(in));
}

template <typename T>
void pass_ff(T&& in) {
    pass(std::forward<T>(in));
}



int main() {
    int a = 4;
    pass_ff(1);
    pass_mv(1);
    pass_ff(a);
    pass_mv(a);

    return 0;
}