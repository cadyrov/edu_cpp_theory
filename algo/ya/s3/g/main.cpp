#include <iostream>

int main() {
    int n;
    std::cin >> n;

    int a = 0;
    int b = 0;
    int c = 0;
    int t;


    for (int i = 0; i < n; ++i ) {
        std::cin >> t;
        if (t == 1) {
            ++b;
        } else if (t == 2){
            ++c;
        } else {
            ++a;
        }
    }


    for (;a >0;--a) {
        std::cout << 0 << " ";
    }

    for (;b >0;--b) {
        std::cout << 1 << " ";
    }

    for (;c >0;--c) {
        std::cout << 2 << " ";
    }

    return 0;
}