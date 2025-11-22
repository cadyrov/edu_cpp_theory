#include <iostream>
#include <cassert>
#include <utility>
#include <vector>

// Task 3: Семантика перемещения (Move Semantics)
//
// Реализуйте класс Vector с корректным перемещением:
// - Vector(Vector&& other) - конструктор перемещения
// - Vector& operator=(Vector&& other) - оператор присваивания перемещением
// - Переместить внутренние данные из other в this

class Vector {
    int* data_;
    size_t size_;
public:
    Vector(size_t size) : size_(size) {
        data_ = new int[size];
        for (size_t i = 0; i < size; ++i) data_[i] = 0;
    }
    
    // TODO: конструктор перемещения
    Vector(Vector&& other) {
        // TODO: реализуйте
    }
    
    // TODO: оператор перемещающего присваивания
    Vector& operator=(Vector&& other) {
        // TODO: реализуйте
        return *this;
    }
    
    ~Vector() { delete[] data_; }
    
    int& operator[](size_t i) { return data_[i]; }
    size_t size() const { return size_; }
};

void testMoveSemantics() {
    Vector v1(5);
    v1[0] = 42;
    
    Vector v2(std::move(v1));
    assert(v2[0] == 42);
    assert(v1.size() == 0);
    
    std::cout << "Move semantics tests passed!\n";
}

int main() {
    testMoveSemantics();
    return 0;
}
