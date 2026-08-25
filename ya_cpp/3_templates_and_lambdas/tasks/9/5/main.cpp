#include <type_traits>
#include <iostream>

template<typename T>
std::ostream& print_value(std::ostream &os, T s) {
    if constexpr(std::is_arithmetic_v<T>) {
        os << "number " << s <<"\n";
    } else {
        os << "string " << s <<"\n";
    }


    return os;
}

int main() {
    print_value(std::cout, 1);
    print_value(std::cout, "vdvds");

    return 0;
}