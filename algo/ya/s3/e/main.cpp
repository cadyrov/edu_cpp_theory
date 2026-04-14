#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int main() {
    int n;
    int budget;
    int result = 0;
    std::vector<int> in{};

    std::cin >> n >> budget;
    in.resize(n);

    for (int i = 0; i < n; ++i ) {
        std::cin >> in[i];
    }

    std::sort(in.begin(), in.end());

    for (int i = 0; i < n; ++i ) {
        if (budget >= in[i]) {
            budget -= in[i];
            ++result;
        } else {
            break;
        }
    }

    std::cout << result << std::endl;

    return 0;
}