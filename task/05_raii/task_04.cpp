#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include <string>

// Task 4: Правило нуля
//
// Реализуйте класс ModernResource, который:
// 1. Использует только RAII-типы (std::unique_ptr, std::vector, std::string)
// 2. Не требует явного деструктора, копирования и перемещения
// 3. Демонстрирует правило нуля

class ModernResource {
    // TODO: Используйте только RAII-типы
    // std::shared_ptr для динамической памяти (поддерживает копирование)
    // std::vector для массивов
    // std::string для строк
    
    std::shared_ptr<int[]> data_;
    std::vector<int> numbers_;
    std::string name_;
    
public:
    // TODO: Конструктор
    ModernResource(const std::string& name, size_t size) {
        // TODO: инициализируйте члены
    }
    
    // TODO: Деструктор НЕ нужен (правило нуля)
    // Деструктор, копирование и перемещение генерируются автоматически
    // Копирование разрешено (используются стандартные типы с копированием)
    
    // Методы доступа
    void setName(const std::string& name) {
        // TODO: реализуйте
    }
    
    const std::string& getName() const {
        // TODO: реализуйте
        static std::string empty;
        return empty;
    }
    
    void addNumber(int value) {
        // TODO: реализуйте добавление в numbers_
    }
    
    size_t getNumberCount() const {
        // TODO: реализуйте
        return 0;
    }
};

// Код для проверки
void testModernResource() {
    ModernResource res("test", 10);
    
    assert(res.getName() == "test");
    
    res.addNumber(1);
    res.addNumber(2);
    res.addNumber(3);
    
    assert(res.getNumberCount() == 3);
    
    // Копирование работает автоматически
    ModernResource copy = res;
    assert(copy.getName() == "test");
    assert(copy.getNumberCount() == 3);
    
    // Перемещение работает автоматически
    ModernResource moved = std::move(res);
    assert(moved.getName() == "test");
    
    // При выходе из функции все ресурсы освобождаются автоматически
    std::cout << "ModernResource (Rule of Zero) tests passed!\n";
}

int main() {
    testModernResource();
    return 0;
}

