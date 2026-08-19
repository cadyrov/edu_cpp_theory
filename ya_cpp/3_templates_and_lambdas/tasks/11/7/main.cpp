// Покажите короткосхемность: функция должна печатать проверяемые значения только до первого `true`
// или `false`.
#include <iostream>

bool print(bool in) {
    std::cout << std::boolalpha << in << std::endl;

    return in;
}

template <typename... Args> void print_all(Args... args) {
    (print(args) && ...);
}

int main() {
    print_all(true, false, true, false);
    return 0;
}