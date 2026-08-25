#include <iostream>
#include <cassert>

int calc(int a, int x, int b, int c){
    return a*x*x + b*x + c;
}

int main() {
    assert(calc(-8, -5, -2, 7) == -183);

    int a;
    int x;
    int b; 
    int c;

    std::cin >> a >> x >> b >> c;

    std::cout << calc(a, x, b, c);
} 