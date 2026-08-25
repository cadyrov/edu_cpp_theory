// Покажите пример, где ошибка в теле функции не является SFINAE.
#include <utility>

template <typename T> void f() {
    typename T::type x; // ошибка уже внутри тела функции
}

int main() {
    f<int>();

    return 0;
}

// clang++ --std=c++23 -o main