#include <iostream>
#include <cassert>
#include <string>
#include <memory>

// Task 5: std::move и передача владения
//
// Реализуйте класс Resource, который управляет ресурсом через std::move:
// - Нельзя копировать
// - Можно перемещать
// - После перемещения исходный объект не владеет ресурсом

class Resource {
    int* data_;
    bool owns_;
public:
    Resource(int value) : owns_(true) {
        data_ = new int(value);
    }
    
    // TODO: delete copy constructor и copy assignment
    
    // TODO: реализуйте move constructor и move assignment
    
    ~Resource() {
        if (owns_) delete data_;
    }
    
    int getValue() const { return *data_; }
};

void testResourceMove() {
    Resource r1(42);
    
    // TODO: Resource r2(std::move(r1));
    // TODO: assert(r2.getValue() == 42);
    
    std::cout << "Resource move tests passed!\n";
}

int main() {
    testResourceMove();
    return 0;
}
