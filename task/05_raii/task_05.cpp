#include <iostream>
#include <cassert>
#include <memory>
#include <stdexcept>

// Task 5: Exception Safety с RAII
//
// Реализуйте класс SafeResource, который:
// 1. Гарантирует освобождение ресурса даже при исключениях
// 2. Демонстрирует strong exception guarantee
// 3. Правильно обрабатывает исключения в конструкторе

class SafeResource {
    int* data_;
    size_t size_;
    
public:
    // TODO: Конструктор с обработкой исключений
    SafeResource(size_t size) : data_(nullptr), size_(0) {
        // TODO: выделите память
        // TODO: если выделение не удалось, выбросьте исключение
        // TODO: если произойдет исключение, ресурс не должен быть создан
    }
    
    // TODO: Деструктор (гарантирует освобождение)
    ~SafeResource() {
        // TODO: освободите ресурс
    }
    
    // TODO: Запретить копирование
    SafeResource(const SafeResource&) = delete;
    SafeResource& operator=(const SafeResource&) = delete;
    
    // TODO: Метод который может выбросить исключение
    void riskyOperation() {
        // TODO: симулируйте операцию которая может выбросить исключение
        // Ресурс должен быть освобожден даже если исключение выброшено
    }
    
    int* getData() { return data_; }
    size_t getSize() const { return size_; }
};

// Код для проверки
void testExceptionSafety() {
    // Нормальное создание
    {
        SafeResource res(100);
        assert(res.getData() != nullptr);
        assert(res.getSize() == 100);
        // Ресурс освободится автоматически
    }
    
    // Тест с исключением в методе
    {
        SafeResource res(50);
        try {
            res.riskyOperation();
        } catch (...) {
            // Ресурс должен быть освобожден даже при исключении
        }
        // Проверка что ресурс освобожден
    }
    
    // Тест с исключением в конструкторе
    try {
        SafeResource res(SIZE_MAX);  // Может выбросить исключение
        assert(false);  // Не должно дойти сюда
    } catch (...) {
        // Ресурс не должен быть создан
    }
    
    std::cout << "Exception safety with RAII tests passed!\n";
}

int main() {
    testExceptionSafety();
    return 0;
}

