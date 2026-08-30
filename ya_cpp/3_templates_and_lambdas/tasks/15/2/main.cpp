// 2. Напишите `requires`-выражение `has_size_v<T>`, проверяющее вызов `.size()`.
#include <iostream>
#include <vector>

template <typename T> inline constexpr bool has_size_v = requires(const T& value) { value.size(); };

struct TTT {
    int value_type;
};
int main() {

    std::cout << has_size_v<int> << "\n";
    std::cout << has_size_v<std::vector<int>> << "\n";

    std::cout << has_size_v<TTT> << "\n";
    std::cout << has_size_v<std::vector<int>> << "\n";

    return 0;
}
