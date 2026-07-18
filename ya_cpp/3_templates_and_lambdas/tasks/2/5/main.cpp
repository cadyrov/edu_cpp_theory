#include <iostream>
#include <type_traits>


template <typename T>
void foo(T& value) {
    static_assert(std::is_const_v<T>);
}



int main() {
    const int a = 0;
    foo(a);



    return 0;
}