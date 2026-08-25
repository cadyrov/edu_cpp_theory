#include <iostream>

int main() {
    int n;

    std::cin >> n;

    int cnt = 0;
    int sumi = 0;
    int nums = 0;
    int val;

    for(int i =0; i < n; ++i) {
        std::cin >> val;
        nums += val;
        sumi += i;

        if (nums == sumi) {
            ++cnt;
            nums = 0;
            sumi = 0;
        }
    }

    std::cout << cnt;

    return 0;
}

