#include <iostream>
#include <string>

int fib(int n,int k) {
    int first = 1;
    int second = 1;
    int third = 2;

    if (n <= 1) {
        return 1;
    }

    for (int i = 2; i < n; ++i) {
        first = second;
        second = third;
        third = (first + second)%k;
    }

    return third;
}

int main() {
    std::string in;

    int n;
    int k;
    int d = 1;

    getline(std::cin, in);

    n = std::stoi(in.substr(0, in.find(' ')));
    k = std::stoi(in.substr(in.find(' ') + 1));
    
    for (int i = 0; i < k; ++i) {
        d *=10;
    }

    std::cout << fib(n, d);

    return 0;
}