#include <iostream>

int main() {
    int n;
    std::cin >> n;

    int res = 1;

    for (int i = 1; i <= n; ++i) {
        res = res * 2 * (2 * i - 1) / (i + 1);
    }

    std::cout << res << std::endl;
    
    return 0;
}
