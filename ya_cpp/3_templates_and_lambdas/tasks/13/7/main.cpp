// 7. Используйте `std::bind_back` и `std::count_if`, чтобы посчитать числа больше `10`.
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 34, 55, 6, 77, 8, 90};
    auto greater_than_10 = std::bind_back(std::greater<>{}, 10);
    auto count = std::count_if(numbers.begin(), numbers.end(), greater_than_10);
    std::cout << count;
}

// clang++ --std=c++23 -o main