//10. Сравните вариант с `template <auto value>` и `template <typename T, T value>`.
#include <cassert>
#include <type_traits>


template <auto value>
struct A {}; // тип value выводится автоматически

template <typename T, T value>
struct B {}; // тип T задается явно

int main() {
    static_assert(std::is_same_v<A<3>, A<3>>);
    static_assert(!std::is_same_v<A<3>, A<'c'>>);

    static_assert(std::is_same_v<B<int, 3>, B<int, 3>>);
    static_assert(!std::is_same_v<B<int, 3>, B<char, 'c'>>);


    return 0;
}