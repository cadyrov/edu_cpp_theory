//1 Напишите функцию, которая использует `typename Container::value_type`.
#include <vector>
#include <iostream>

template<typename Container>
typename Container::value_type first(const Container& c){
    return c.front();
}

int main() {
    std::vector<int> a{1};
    
    std::cout << first(a) << "\n";


    return 0;
}