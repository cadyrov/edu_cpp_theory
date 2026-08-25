#include <type_traits>

template<typename T, typename = void>
struct IsContainer : std::false_type {};

template<typename T>
struct IsContainer<T, std::void_t<typename T::value_type>>
    : std::true_type {};

    
int main() {
    return 0;
}