#include <type_traits>

template <typename T>
struct IsInt: std::false_type{};

template <>
struct IsInt<int>: std::true_type{};

int main() {
    static_assert(!IsInt<float>::value);
    static_assert(IsInt<int>::value);

    return 0;
}
