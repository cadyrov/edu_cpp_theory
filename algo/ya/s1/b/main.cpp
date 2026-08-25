#include <iostream>
#include <cassert>

bool calc(int a, int b, int c){
    return a%2 == b%2 == c%2;
}

int main() {
    assert(calc(1, 2, -3) == false);
    assert(calc(1, 1, 1) == true);

    int a;
    int b; 
    int c;

    std::cin >> a >> b >> c;

    if ( calc(a, b, c) ){
        std::cout << "WIN";
        
        return 0;
    }

    std::cout << "FAIL";
} 