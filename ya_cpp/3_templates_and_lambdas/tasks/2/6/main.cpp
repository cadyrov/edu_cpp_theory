#include <type_traits>

template<typename T>
void foo(const T& value) {
    static_assert(std::is_same_v<T, int*>);
}


int main() {
    int  z = 10;
    int* const p = &z;

    foo(p);

    return 0;
}