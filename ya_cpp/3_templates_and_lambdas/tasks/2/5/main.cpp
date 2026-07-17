#include <iostream>
#include <typeinfo>

template<typename T>
void foo(T& value){
    std::cout << typeid(value).name()<< value << "\n";
}

int main(){
    const int a = 10;

    foo(a);

    return 0;
}
