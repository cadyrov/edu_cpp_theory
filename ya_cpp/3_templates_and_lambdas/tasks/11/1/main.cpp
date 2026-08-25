#include <cstddef>

template <typename... Args> constexpr std::size_t count_args(Args... args) {
    return sizeof...(args);
}