#include <iostream>
#include <cassert>

// Task 1: Базовое использование new/delete
//
// Реализуйте класс IntWrapper, который:
// 1. Хранит указатель на int, выделенный через new
// 2. Правильно освобождает память в деструкторе
// 3. Предоставляет методы для установки и получения значения
// 4. Защищен от утечек памяти

class IntWrapper {
    int* value_;
public:
    // TODO: Конструктор по умолчанию (выделяет память для int)
    IntWrapper() {
        // TODO: реализуйте
    }
    
    // TODO: Конструктор с параметром
    IntWrapper(int value) {
        // TODO: реализуйте
    }
    
    // TODO: Деструктор (освобождает память)
    ~IntWrapper() {
        // TODO: реализуйте
    }
    
    // TODO: Метод для установки значения
    void setValue(int value) {
        // TODO: реализуйте
    }
    
    // TODO: Метод для получения значения
    int getValue() const {
        // TODO: реализуйте
        return 0;
    }
};

// Код для проверки
void testIntWrapper() {
    // Тест конструктора по умолчанию
    IntWrapper w1;
    w1.setValue(42);
    assert(w1.getValue() == 42);
    
    // Тест конструктора с параметром
    IntWrapper w2(100);
    assert(w2.getValue() == 100);
    
    // Тест изменения значения
    w2.setValue(200);
    assert(w2.getValue() == 200);
    
    std::cout << "IntWrapper tests passed!\n";
}

int main() {
    testIntWrapper();
    return 0;
}

