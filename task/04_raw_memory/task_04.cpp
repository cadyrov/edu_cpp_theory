#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstring>

// Task 4: Выравнивание памяти
//
// Реализуйте функции для работы с выровненной памятью:
// 1. Функция для выделения памяти с заданным выравниванием
// 2. Функция для освобождения выровненной памяти
// 3. Проверка корректности выравнивания

// TODO: Выделить память с заданным выравниванием
// Используйте std::aligned_alloc или new с align_val_t
void* allocateAligned(size_t size, size_t alignment) {
    // TODO: реализуйте выделение выровненной памяти
    return nullptr;
}

// TODO: Освободить выровненную память
void deallocateAligned(void* ptr) {
    // TODO: реализуйте освобождение памяти
}

// TODO: Проверить, что указатель выровнен правильно
bool isAligned(void* ptr, size_t alignment) {
    // TODO: реализуйте проверку выравнивания
    return false;
}

// Код для проверки
void testAlignment() {
    const size_t alignment = 64;
    const size_t size = 1024;
    
    // Выделение памяти с выравниванием
    void* ptr = allocateAligned(size, alignment);
    assert(ptr != nullptr);
    
    // Проверка выравнивания
    assert(isAligned(ptr, alignment));
    
    // Использование памяти
    int* int_ptr = static_cast<int*>(ptr);
    int_ptr[0] = 42;
    assert(int_ptr[0] == 42);
    
    // Освобождение памяти
    deallocateAligned(ptr);
    
    std::cout << "Alignment tests passed!\n";
}

int main() {
    testAlignment();
    return 0;
}

