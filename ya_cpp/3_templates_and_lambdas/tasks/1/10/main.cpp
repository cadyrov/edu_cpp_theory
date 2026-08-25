#include <iostream>

template<typename F>
void call_and_print(F&& fn) {
    std::cout << fn() << "\n";
}