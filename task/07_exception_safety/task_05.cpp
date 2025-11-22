#include <iostream>
#include <cassert>
#include <memory>
#include <stdexcept>

// Task 5: Деструкторы и noexcept
//
// Реализуйте класс SafeDestructor, который:
// 1. Имеет деструктор помеченный как noexcept
// 2. Правильно обрабатывает исключения в деструкторе
// 3. Гарантирует освобождение ресурсов

class SafeDestructor {
    std::unique_ptr<int[]> data_;
    size_t size_;
    
public:
    // TODO: Конструктор
    SafeDestructor(size_t size) : size_(size) {
        // TODO: выделите память
    }
    
    // TODO: Деструктор (должен быть noexcept)
    ~SafeDestructor() noexcept {
        // TODO: освободите ресурсы
        // TODO: если в деструкторе может произойти исключение,
        // TODO: обработайте его внутри (не пробрасывайте наружу)
    }
    
    // TODO: Метод очистки (может выбросить исключение)
    void cleanup() {
        // TODO: симулируйте операцию очистки
        // TODO: может выбросить исключение
    }
    
    size_t getSize() const { return size_; }
};

// Код для проверки
void testDestructorNoexcept() {
    // Нормальное использование
    {
        SafeDestructor obj(100);
        assert(obj.getSize() == 100);
        // Деструктор вызовется автоматически
    }
    
    // Проверка что деструктор noexcept
    static_assert(noexcept(std::declval<SafeDestructor>().~SafeDestructor()),
                  "Destructor should be noexcept");
    
    // Тест что ресурсы освобождаются даже при исключении
    {
        SafeDestructor obj(50);
        try {
            obj.cleanup();
            throw std::runtime_error("Test");
        } catch (...) {
            // Деструктор должен быть вызван и не должен бросать исключение
        }
    }
    
    std::cout << "Destructor noexcept tests passed!\n";
}

int main() {
    testDestructorNoexcept();
    return 0;
}

