#include <iostream>
#include <cassert>
#include <memory>
#include <mutex>
#include <stdexcept>

// Task 4: RAII и исключения
//
// Реализуйте классы для демонстрации:
// 1. Автоматическое освобождение ресурсов при исключениях
// 2. Использование lock_guard для мьютексов
// 3. Гарантия освобождения даже при исключениях

class Resource {
    int value_;
public:
    Resource(int v) : value_(v) {
        std::cout << "Resource " << value_ << " created\n";
    }
    ~Resource() {
        std::cout << "Resource " << value_ << " destroyed\n";
    }
    int getValue() const { return value_; }
};

class SafeManager {
    std::unique_ptr<Resource> resource_;
    std::mutex mutex_;
    
public:
    // TODO: Метод создания ресурса с защитой мьютексом
    void createResource(int value) {
        // TODO: используйте std::lock_guard для защиты
        // TODO: создайте ресурс через make_unique
        // TODO: даже при исключении мьютекс освободится
    }
    
    // TODO: Метод работы с ресурсом
    void useResource() {
        // TODO: используйте lock_guard
        // TODO: получите доступ к ресурсу
        // TODO: симулируйте операцию которая может выбросить исключение
    }
    
    // TODO: Метод проверки наличия ресурса
    bool hasResource() const {
        // TODO: проверьте наличие ресурса
        return false;
    }
};

// Код для проверки
void testRAIIWithExceptions() {
    SafeManager manager;
    
    // Создание ресурса
    manager.createResource(42);
    assert(manager.hasResource());
    
    // Тест что ресурс освобождается при исключении
    {
        SafeManager local_manager;
        try {
            local_manager.createResource(100);
            // Симуляция исключения
            throw std::runtime_error("Test exception");
        } catch (...) {
            // Ресурс должен быть освобожден автоматически
        }
        // Проверка что ресурс освобожден
    }
    
    // Тест что мьютекс освобождается даже при исключении
    try {
        manager.useResource();
    } catch (...) {
        // Мьютекс должен быть освобожден автоматически
    }
    
    std::cout << "RAII with exceptions tests passed!\n";
}

int main() {
    testRAIIWithExceptions();
    return 0;
}

