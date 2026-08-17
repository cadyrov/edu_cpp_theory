#include <type_traits>

template <typename T, typename U>
struct IsSame : std::false_type{};

template <typename T>
struct IsSame<T, T> : std::true_type{};


int main() {
    static_assert(IsSame<int, int>::value);
    static_assert(!IsSame<int, float>::value);

    return 0;
}