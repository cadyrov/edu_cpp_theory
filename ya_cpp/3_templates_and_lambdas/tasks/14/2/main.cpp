//  Напишите две перегрузки `print`: для указателей и для остальных типов.
#include <iostream>
#include <type_traits>

template <typename T>
std::enable_if_t<!std::is_pointer_v<T>, std::ostream&> print(std::ostream& os, T in) {
    os << in;

    return os;
}

template <typename T>
std::enable_if_t<std::is_pointer_v<T>, std::ostream&> print(std::ostream& os, T in) {
    if (in == nullptr) {
        os << "null";
    } else {
        os << *in;
    }

    return os;
}

int main() {
    int a = 9;
    int* p = &a;

    print(std::cout, a);
    print(std::cout, " ");
    print(std::cout, p);
    print(std::cout, nullptr);

    return 0;
}

// clang++ --std=c++23 -o main