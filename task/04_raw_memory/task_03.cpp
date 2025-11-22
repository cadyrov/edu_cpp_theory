#include <iostream>
#include <cassert>
#include <new>

// Task 3: Размещающий new (placement new)
//
// Реализуйте класс PlacementBuffer, который:
// 1. Использует размещающий new для создания объектов в предварительно выделенном буфере
// 2. Правильно вызывает деструкторы через явный вызов
// 3. Поддерживает создание и уничтожение объектов в буфере

class SimpleObject {
    int value_;
public:
    SimpleObject(int v) : value_(v) {
        std::cout << "SimpleObject constructed with value: " << value_ << "\n";
    }
    
    ~SimpleObject() {
        std::cout << "SimpleObject destroyed with value: " << value_ << "\n";
    }
    
    int getValue() const { return value_; }
    void setValue(int v) { value_ = v; }
};

class PlacementBuffer {
    alignas(SimpleObject) char buffer_[sizeof(SimpleObject)];
    bool occupied_;
    
public:
    PlacementBuffer() : occupied_(false) {}
    
    // TODO: Создать объект в буфере используя placement new
    SimpleObject* create(int value) {
        // TODO: реализуйте создание объекта через placement new
        return nullptr;
    }
    
    // TODO: Уничтожить объект в буфере (явный вызов деструктора)
    void destroy(SimpleObject* obj) {
        // TODO: реализуйте явный вызов деструктора
    }
    
    bool isOccupied() const { return occupied_; }
};

// Код для проверки
void testPlacementBuffer() {
    PlacementBuffer buffer;
    
    // Создание объекта в буфере
    SimpleObject* obj = buffer.create(42);
    assert(obj != nullptr);
    assert(obj->getValue() == 42);
    assert(buffer.isOccupied());
    
    // Изменение значения
    obj->setValue(100);
    assert(obj->getValue() == 100);
    
    // Уничтожение объекта
    buffer.destroy(obj);
    assert(!buffer.isOccupied());
    
    std::cout << "PlacementBuffer tests passed!\n";
}

int main() {
    testPlacementBuffer();
    return 0;
}

