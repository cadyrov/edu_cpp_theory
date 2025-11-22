#include <iostream>
#include <cassert>
#include <new>
#include <stdexcept>
#include <cstdint>
#include <climits>

// Task 5: Обработка исключений при выделении памяти
//
// Реализуйте класс SafeAllocator, который:
// 1. Обрабатывает исключение std::bad_alloc при выделении памяти
// 2. Предоставляет безопасные методы выделения памяти
// 3. Возвращает nullptr вместо выбрасывания исключения при нехватке памяти

class SafeAllocator {
public:
    // TODO: Выделить память с обработкой исключений
    // Возвращает nullptr если память не удалось выделить
    static void* allocate(size_t size) noexcept {
        // TODO: реализуйте выделение с обработкой bad_alloc
        return nullptr;
    }
    
    // TODO: Выделить массив с обработкой исключений
    static void* allocateArray(size_t count, size_t element_size) noexcept {
        // TODO: реализуйте выделение массива с обработкой bad_alloc
        return nullptr;
    }
    
    // TODO: Освободить память
    static void deallocate(void* ptr) noexcept {
        // TODO: реализуйте освобождение
    }
    
    // TODO: Освободить массив
    static void deallocateArray(void* ptr) noexcept {
        // TODO: реализуйте освобождение массива
    }
};

// Код для проверки
void testSafeAllocator() {
    // Тест обычного выделения
    void* ptr1 = SafeAllocator::allocate(100);
    assert(ptr1 != nullptr);
    SafeAllocator::deallocate(ptr1);
    
    // Тест выделения массива
    void* ptr2 = SafeAllocator::allocateArray(10, sizeof(int));
    assert(ptr2 != nullptr);
    SafeAllocator::deallocateArray(ptr2);
    
    // Тест обработки нехватки памяти (если возможно)
    // В реальном коде это может не сработать, но структура должна быть правильной
    void* huge_ptr = SafeAllocator::allocate(static_cast<size_t>(-1));
    assert(huge_ptr == nullptr);  // Должен вернуть nullptr, а не выбросить исключение
    
    std::cout << "SafeAllocator tests passed!\n";
}

int main() {
    testSafeAllocator();
    return 0;
}

