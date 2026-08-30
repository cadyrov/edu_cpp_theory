// 1. Напишите `requires`-выражение `has_value_type_v<T>`, проверяющее `typename T::value_type`.
#include <iostream>
#include <vector>

template <typename T> inline constexpr bool has_value_type_v = requires { typename T::value_type; };
template <typename T> inline constexpr bool has_value_v = requires { T::value_type; };

struct TTT {
    int value_type;
};
int main() {

    std::cout << has_value_type_v<int> << "\n";
    std::cout << has_value_type_v<std::vector<int>> << "\n";

    std::cout << has_value_v<TTT> << "\n";
    std::cout << has_value_v<std::vector<int>> << "\n";

    return 0;
}
