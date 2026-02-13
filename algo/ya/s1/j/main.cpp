#include <iostream>
#include <cassert>
#include <string>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    int x = 2;

    for (;x <= n;) {
        for (;n%x==0;) {
            std::cout << x << " ";
            n /=x;
        }
        
        ++x;
    }


} 