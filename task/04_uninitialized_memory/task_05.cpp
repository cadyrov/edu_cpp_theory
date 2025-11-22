#include <iostream>
#include <cassert>
#include <memory>
#include <stdexcept>

// Task 5: Exception safety при работе с неинициализированной памятью
//
// Реализуйте класс SafeBuffer, который:
// 1. Выделяет память без инициализации
// 2. Инициализирует элементы с обработкой исключений
// 3. Гарантирует отсутствие утечек памяти при исключениях

class SafeBuffer {
    int* data_;
    size_t size_;
    
public:
    SafeBuffer() : data_(nullptr), size_(0) {}
    
    // TODO: Выделить память и инициализировать элементы значением
    // Должен быть exception-safe (strong guarantee)
    void initialize(size_t count, int value) {
        // TODO: выделите память через operator new[]
        // TODO: используйте try-catch для обработки исключений
        // TODO: при исключении освободите память
    }
    
    // TODO: Освободить память с вызовом деструкторов
    void clear() {
        // TODO: используйте std::destroy_n
        // TODO: освободите память через operator delete[]
    }
    
    ~SafeBuffer() {
        clear();
    }
    
    int* get() { return data_; }
    const int* get() const { return data_; }
    size_t size() const { return size_; }
};

// Код для проверки
void testExceptionSafety() {
    SafeBuffer buffer;
    
    // Нормальная инициализация
    buffer.initialize(10, 42);
    assert(buffer.size() == 10);
    assert(buffer.get() != nullptr);
    
    // Проверка значений
    for (size_t i = 0; i < buffer.size(); ++i) {
        assert(buffer.get()[i] == 42);
    }
    
    // Переинициализация
    buffer.clear();
    buffer.initialize(5, 100);
    assert(buffer.size() == 5);
    
    buffer.clear();
    
    std::cout << "Exception safety tests passed!\n";
}

int main() {
    testExceptionSafety();
    return 0;
}

