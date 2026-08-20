//  Используйте std::count_if, чтобы посчитать строки длиннее заданного лимита.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    size_t limit = 2;
    std::vector<std::string> data{"d", "cdscds", "cdc", "cd"};

    auto cnt = std::count_if(data.begin(), data.end(),
                             [limit](const std::string& a) { return a.size() > limit; });

    std::cout << cnt;

    return 0;
}