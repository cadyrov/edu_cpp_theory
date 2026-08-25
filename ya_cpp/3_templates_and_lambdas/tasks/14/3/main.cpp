//   Напишите `size_of`, где наличие `.size()` проверяется в возвращаемом типе через `decltype`.
#include <utility>

template <typename Container, typename = decltype(declval<const Container&>().size())>
auto size_of(const Container& in) {
    return in.size();
}

int main() {
    int a = 9;
    int* p = &a;

    return 0;
}

// clang++ --std=c++23 -o main