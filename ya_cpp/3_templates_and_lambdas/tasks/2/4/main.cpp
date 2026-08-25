#include <iostream>

template<typename T>
void foo(T in){
    std::cout <<  in <<"\n";
}


int main() {
    const int a = 10;

    foo(10);

    return 0;
}