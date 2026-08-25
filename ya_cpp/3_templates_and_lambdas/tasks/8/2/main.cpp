//Напишите `print_first`, который принимает контейнер и печатает первый элемент.
#include <vector>
#include <iostream>

template<typename Container>
void print_first(const Container& c){
    std::cout << c.front()<< "\n";
}

int main() {
    std::vector<int> a{1};
    
    print_first(a);

    return 0;
}