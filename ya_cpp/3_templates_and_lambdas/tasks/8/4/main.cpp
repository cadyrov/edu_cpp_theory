 //Используйте `Container::value_type` для проверки типа элементов.
#include<array>

template <typename T, typename T1>
struct SameType{};

template <typename T>
struct SameType<T, T> {
    using type = T;
};

template <
    typename T, 
    typename Container, 
    typename = typename SameType<T, typename Container::value_type>::type
>
class Wrapper{
    Container storage_;
};

int main() {
    Wrapper<int, std::array<int, 4>> a;

    return 0;
}