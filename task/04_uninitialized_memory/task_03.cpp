#include <iostream>
#include <cassert>
#include <new>
#include <string>

// Task 3: Placement new для объектов
//
// Реализуйте класс ObjectBuffer, который:
// 1. Хранит буфер для размещения объекта через placement new
// 2. Создает объект в буфере
// 3. Правильно вызывает деструктор при уничтожении

class SimpleObject {
    int value_;
    std::string name_;
public:
    SimpleObject(int v, const std::string& n) 
        : value_(v), name_(n) {
        std::cout << "SimpleObject constructed: " << name_ << "\n";
    }
    
    ~SimpleObject() {
        std::cout << "SimpleObject destroyed: " << name_ << "\n";
    }
    
    int getValue() const { return value_; }
    const std::string& getName() const { return name_; }
};

class ObjectBuffer {
    alignas(SimpleObject) unsigned char buffer_[sizeof(SimpleObject)];
    bool occupied_;
    
public:
    ObjectBuffer() : occupied_(false) {}
    
    // TODO: Создать объект в буфере используя placement new
    SimpleObject* create(int value, const std::string& name) {
        // TODO: используйте placement new для создания объекта
        return nullptr;
    }
    
    // TODO: Уничтожить объект в буфере
    void destroy(SimpleObject* obj) {
        // TODO: явно вызовите деструктор объекта
    }
    
    bool isOccupied() const { return occupied_; }
};

// Код для проверки
void testPlacementNew() {
    ObjectBuffer buffer;
    
    // Создание объекта в буфере
    SimpleObject* obj = buffer.create(42, "test");
    assert(obj != nullptr);
    assert(obj->getValue() == 42);
    assert(obj->getName() == "test");
    assert(buffer.isOccupied());
    
    // Уничтожение объекта
    buffer.destroy(obj);
    assert(!buffer.isOccupied());
    
    std::cout << "Placement new tests passed!\n";
}

int main() {
    testPlacementNew();
    return 0;
}

