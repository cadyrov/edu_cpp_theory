#include <type_traits>

template<typename Expected,typename T>
void foo(T*) {
    static_assert(std::is_same_v<T, Expected>);
}

int main() {
    int x = 1;

    int* z = &x;
    const int* w= &x;

    foo<int>(z);
    foo<const int>(w);


    return 0;
}