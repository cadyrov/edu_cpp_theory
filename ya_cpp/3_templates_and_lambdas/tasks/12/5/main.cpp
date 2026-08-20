//  Используйте `std::find_if`, чтобы найти первый четный элемент.

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> data{1, 2, 3, 4, 5};

    auto it = std::find_if(data.begin(), data.end(), [](int a) { return a % 2 == 0; });

    if (it != data.end()) {
        std::cout << *it;
    }

    return 0;
}