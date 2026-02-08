#include <iostream>
#include <cassert>
#include <string>

int main() {
    int n;

    std::cin >> n;

    if (n == 0 ) {
        std::cout << '0';

        return 0;
    }

    std::string data;

    for (;n > 0;) {
        if (n%2 == 1) {
            data.push_back('1');
        } else {
            data.push_back('0');
        }

        n = n/2;
    }

    for (int i = data.size()-1; i >= 0; --i) {
        std::cout << data[i];
    }
} 