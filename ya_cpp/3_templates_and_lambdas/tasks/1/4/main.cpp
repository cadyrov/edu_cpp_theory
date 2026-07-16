#include <iostream>

template<typename T>
void print_type_size(T){
    std::cout << sizeof(T) <<"\n";
}