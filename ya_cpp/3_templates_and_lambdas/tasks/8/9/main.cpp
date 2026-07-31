//9. Используйте `static_assert`, чтобы проверить совместимость `T` и `Container::value_type`.
#include <type_traits>
#include<array>

template <
    typename T, 
    typename Container
>
class Wrapper{
    static_assert(std::is_same_v<T, typename Container::value_type>);
    Container storage_;
};

int main() {
    Wrapper<int, std::array<int, 4>> a;

    return 0;
}