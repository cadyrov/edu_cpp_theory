// Используйте std::sort с лямбдой-компаратором для сортировки по убыванию.

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> data{1, 2, 3, 4, 5};

    std::sort(data.begin(), data.end(), [](int a, int b) { return a > b; });

    for (auto s : data) {
        std::cout << s << "\n";
    }
    return 0;
}