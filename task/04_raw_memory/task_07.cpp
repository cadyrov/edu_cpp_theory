#include <iostream>
#include <cassert>
#include <cstdlib>

// Task 7: Кастомные операторы new/delete
//
// Реализуйте класс CustomAllocator, который:
// 1. Переопределяет операторы new и delete для класса
// 2. Использует кастомную стратегию выделения памяти
// 3. Ведет статистику выделений и освобождений

static size_t allocation_count = 0;
static size_t deallocation_count = 0;
static size_t total_allocated = 0;

class CustomAllocator {
    int value_;
    
public:
    CustomAllocator(int v) : value_(v) {}
    
    // TODO: Переопределить operator new
    static void* operator new(size_t size) noexcept {
        // TODO: реализуйте кастомное выделение памяти
        // Обновите статистику
        return nullptr;
    }
    
    // TODO: Переопределить operator delete
    static void operator delete(void* ptr) noexcept {
        // TODO: реализуйте кастомное освобождение памяти
        // Обновите статистику
    }
    
    // TODO: Переопределить operator new[] для массивов
    static void* operator new[](size_t size) noexcept {
        // TODO: реализуйте
        return nullptr;
    }
    
    // TODO: Переопределить operator delete[] для массивов
    static void operator delete[](void* ptr) noexcept {
        // TODO: реализуйте
    }
    
    int getValue() const { return value_; }
    
    // Статистика
    static size_t getAllocationCount() { return allocation_count; }
    static size_t getDeallocationCount() { return deallocation_count; }
    static size_t getTotalAllocated() { return total_allocated; }
};

// Код для проверки
void testCustomAllocator() {
    // Сброс статистики
    allocation_count = 0;
    deallocation_count = 0;
    total_allocated = 0;
    
    // Выделение одного объекта
    CustomAllocator* obj = new CustomAllocator(42);
    assert(obj != nullptr);
    assert(obj->getValue() == 42);
    assert(CustomAllocator::getAllocationCount() == 1);
    
    // Выделение массива (требует конструктор по умолчанию)
    // CustomAllocator* arr = new CustomAllocator[5];
    // assert(arr != nullptr);
    
    // Освобождение
    delete obj;
    assert(CustomAllocator::getDeallocationCount() == 1);
    
    // delete[] arr;
    
    std::cout << "Allocations: " << CustomAllocator::getAllocationCount() << "\n";
    std::cout << "Deallocations: " << CustomAllocator::getDeallocationCount() << "\n";
    std::cout << "CustomAllocator tests passed!\n";
}

int main() {
    testCustomAllocator();
    return 0;
}

