#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstddef>
#include <cstdint>

// Task 9: Аллокатор с выравниванием
//
// Реализуйте класс AlignedAllocator, который:
// 1. Выделяет память с заданным выравниванием
// 2. Правильно освобождает выровненную память
// 3. Поддерживает выделение массивов с выравниванием
// 4. Проверяет корректность выравнивания

class AlignedAllocator {
    size_t alignment_;
    
public:
    explicit AlignedAllocator(size_t alignment) : alignment_(alignment) {
        // Проверка что alignment является степенью двойки
        assert((alignment & (alignment - 1)) == 0);
    }
    
    // TODO: Выделить память с выравниванием
    void* allocate(size_t size) {
        // TODO: реализуйте выделение с учетом выравнивания
        // Подсказка: нужно выделить size + alignment байт и найти выровненный адрес
        return nullptr;
    }
    
    // TODO: Освободить выровненную память
    void deallocate(void* ptr) {
        // TODO: реализуйте освобождение
        // Подсказка: нужно восстановить оригинальный указатель
    }
    
    // TODO: Выделить массив с выравниванием
    void* allocateArray(size_t count, size_t element_size) {
        // TODO: реализуйте выделение массива
        return nullptr;
    }
    
    // TODO: Освободить массив
    void deallocateArray(void* ptr) {
        // TODO: реализуйте освобождение массива
    }
    
    size_t getAlignment() const { return alignment_; }
};

// Код для проверки
void testAlignedAllocator() {
    AlignedAllocator allocator(64);
    
    // Выделение памяти
    void* ptr = allocator.allocate(1024);
    assert(ptr != nullptr);
    
    // Проверка выравнивания
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    assert((addr % allocator.getAlignment()) == 0);
    
    // Использование памяти
    int* int_ptr = static_cast<int*>(ptr);
    int_ptr[0] = 42;
    assert(int_ptr[0] == 42);
    
    // Освобождение
    allocator.deallocate(ptr);
    
    // Тест массива
    void* arr = allocator.allocateArray(10, sizeof(int));
    assert(arr != nullptr);
    uintptr_t arr_addr = reinterpret_cast<uintptr_t>(arr);
    assert((arr_addr % allocator.getAlignment()) == 0);
    
    allocator.deallocateArray(arr);
    
    std::cout << "AlignedAllocator tests passed!\n";
}

int main() {
    testAlignedAllocator();
    return 0;
}

