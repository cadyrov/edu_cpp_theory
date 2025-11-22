#include <iostream>
#include <cassert>

// Task 1: Базовое использование RAII
//
// Реализуйте класс IntResource, который:
// 1. Выделяет память для int в конструкторе
// 2. Освобождает память в деструкторе
// 3. Предоставляет методы для работы с ресурсом
// 4. Демонстрирует автоматическое освобождение ресурса

class IntResource {
    int* value_;
    
public:
    // TODO: Конструктор (выделяет память)
    IntResource(int initial_value = 0) {
        // TODO: выделите память через new
    }
    
    // TODO: Деструктор (освобождает память)
    ~IntResource() {
        // TODO: освободите память через delete
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
    
    // TODO: Запретить копирование (для простоты)
    IntResource(const IntResource&) = delete;
    IntResource& operator=(const IntResource&) = delete;
};

// Код для проверки
void testIntResource() {
    {
        IntResource res(42);
        assert(res.getValue() == 42);
        
        res.setValue(100);
        assert(res.getValue() == 100);
        
        // При выходе из блока деструктор автоматически освободит память
    }
    
    // Память должна быть освобождена автоматически
    std::cout << "IntResource tests passed!\n";
}

int main() {
    testIntResource();
    return 0;
}

