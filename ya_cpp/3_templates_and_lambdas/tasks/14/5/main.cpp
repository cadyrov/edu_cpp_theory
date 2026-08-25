// Напишите `HasSize<T>` через `std::void_t` и `std::declval<const T&>()`.
#include <type_traits>
#include <utility>

template <typename, typename = void> struct HasSize : std::false_type {};

template <typename T>
struct HasSize<T, std::void_t<decltype(std::declval<const T&>().size())>> : std::true_type {};

template <typename T> inline constexpr bool has_size_v = HasSize<T>::value;

int main() {}

// clang++ --std=c++23 -o main