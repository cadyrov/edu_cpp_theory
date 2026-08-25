#include <algorithm>
#include <vector>
#include <iterator>
#include <string>

template <class Container>
constexpr size_t findUniqueCount(const Container& items) {
    using V  = std::iter_value_t<decltype(std::begin(items))>;
    std::vector<V> data(std::begin(items), std::end(items));

    std::sort(data.begin(), data.end());

    return std::unique(data.begin(), data.end()) - data.begin();
}

int main() {
    static_assert(findUniqueCount(std::vector<std::string>{"a", "c", "c", "z", "z", "a"}) == 3);
    static_assert(findUniqueCount(std::vector{1, 2, 100, 11, 22, 22, 2}) == 5);
    return 0;
} 