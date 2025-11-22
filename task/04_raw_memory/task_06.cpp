#include <iostream>
#include <cassert>

// Task 6: RAII с сырой памятью
//
// Реализуйте класс RawMemory, который:
// 1. Использует RAII для управления сырой памятью
// 2. Правильно освобождает память в деструкторе
// 3. Запрещает копирование (delete copy constructor и assignment)
// 4. Поддерживает перемещение (move constructor и assignment)

class RawMemory {
    void* ptr_;
    size_t size_;
    
public:
    // TODO: Конструктор (выделяет память)
    RawMemory(size_t size) {
        // TODO: реализуйте выделение памяти
    }
    
    // TODO: Деструктор (освобождает память)
    ~RawMemory() {
        // TODO: реализуйте освобождение памяти
    }
    
    // TODO: Запретить копирование
    RawMemory(const RawMemory&) = delete;
    RawMemory& operator=(const RawMemory&) = delete;
    
    // TODO: Конструктор перемещения
    RawMemory(RawMemory&& other) noexcept {
        // TODO: реализуйте перемещение
    }
    
    // TODO: Оператор присваивания перемещением
    RawMemory& operator=(RawMemory&& other) noexcept {
        // TODO: реализуйте перемещение
        return *this;
    }
    
    // Методы доступа
    void* get() { return ptr_; }
    const void* get() const { return ptr_; }
    size_t size() const { return size_; }
};

// Код для проверки
void testRawMemory() {
    // Тест создания
    RawMemory mem(1024);
    assert(mem.get() != nullptr);
    assert(mem.size() == 1024);
    
    // Тест перемещения
    RawMemory mem2 = std::move(mem);
    assert(mem2.get() != nullptr);
    assert(mem2.size() == 1024);
    assert(mem.get() == nullptr);  // После перемещения должен быть nullptr
    
    // Эти строки НЕ должны компилироваться:
    // RawMemory mem3 = mem2;  // Копирование запрещено
    // mem = mem2;             // Присваивание запрещено
    
    std::cout << "RawMemory tests passed!\n";
}

int main() {
    testRawMemory();
    return 0;
}

