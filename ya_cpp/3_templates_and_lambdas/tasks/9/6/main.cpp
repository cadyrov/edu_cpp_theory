#include <type_traits>
#include <iostream>

void process(std::true_type) {
    std::cout << 1;
}

void process(std::false_type) {
    std::cout << 0;
}


int main() {
    process(std::is_integral<int>{});
    process(std::is_integral<double>{});

}