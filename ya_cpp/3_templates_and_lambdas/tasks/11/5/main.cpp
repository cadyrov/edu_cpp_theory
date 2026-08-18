// 5. Напишите `print_with_space`, используя fold expression по оператору `,`.
#include <iostream>

template <typename T> void print_space(T in) {
    std::cout << in << " ";
}

template <typename... Args> void print_with_space(Args... args) {
    (print_space(args), ..., (std::cout << std::endl));
}

int main() {
    print_with_space(2, 3, 4, 5);

    return 0;
}