#include <iostream>
#include <typeinfo>

template<typename T>
void print(T in) {
    std::cout << typeid(in).name() << in << "\n";
}

void print(int in) {
    std::cout << "int " << in << "\n";
}

void print(double in) {
    std::cout <<"double "<< in << "\n";
}


int main() {
    print(10);
    print(10.);
    print('0');
    print("clsudh");

    return 0;
}