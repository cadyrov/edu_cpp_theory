#include <iostream>

template <typename... Args> void print_all(Args... args) {
    ((std::cout << args << ' '), ...);
}

int main() {
    print_all(1, 2, 3, 4, 5);

    return 0;
}
