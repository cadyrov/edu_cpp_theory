#include <type_traits>

template<typename T>
struct IsBool : std::false_type{};

template<>
struct IsBool<bool> : std::true_type{};


int main() {
    static_assert(!IsBool<int>::value);

    return 0;
}