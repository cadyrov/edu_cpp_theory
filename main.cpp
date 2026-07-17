#include <iostream>
#include <print>
#include <ranges>
#include <string>

namespace my_views {

template <std::ranges::view V>
    requires std::ranges::bidirectional_range<V> && std::ranges::common_range<V>
class trim_view : public std::ranges::view_interface<trim_view<V>> {

    V base_;

    static constexpr bool is_space(char ch) {
        return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\f' || ch == '\v';
    }

public:
    trim_view() = default;

    // конструкторы
    constexpr explicit trim_view(V base) : base_(std::move(base)) {}

    constexpr auto begin() {
        auto first = std::ranges::begin(base_);
        auto last = std::ranges::end(base_);

        while (first != last && is_space(*first)) {
            ++first;
        }

        return first;
    }

    constexpr auto end() {
        auto first = std::ranges::begin(base_);
        auto last = std::ranges::end(base_);

        while (first != last) {
            auto prev = last;
            --prev;

            if (!is_space(*prev)) {
                break;
            }

            last = prev;
        }

        return last;
    }

};

// Адаптер
struct TrimAdaptor : public std::ranges::range_adaptor_closure<TrimAdaptor> {
    template <std::ranges::viewable_range R>
    constexpr auto operator()(R &&r) const {
        return trim_view(std::views::all(std::forward<R>(r)));
    }
};

inline constexpr auto trim = TrimAdaptor{};
}  // namespace my_views

int main() {
    // Простой тест
    std::println("Basic test");
    std::string str{"   Hello world!   "};

    std::println("Original: ");
    for (auto i : str) {
        std::print("{}", i);
    }
    std::println("");

    std::println("Trim: ");
    for (auto i : str | my_views::trim) {
        std::print("{}", i);
    }
}
