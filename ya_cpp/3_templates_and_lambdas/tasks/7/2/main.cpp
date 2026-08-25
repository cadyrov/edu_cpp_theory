//Проверьте, как она принимает lvalue и rvalue.
#include <cassert>
#include <cmath>
#include <type_traits>

template <typename T>
void pass(T&&) {
  if constexpr (std::is_lvalue_reference_v<T>) {
        static_assert(std::is_same_v<T, int&>);
    } else {
        static_assert(std::is_same_v<T, int>);
    }
}

int main() {
    int a =9;
    pass(a);
    pass(4);

    return 0;
}