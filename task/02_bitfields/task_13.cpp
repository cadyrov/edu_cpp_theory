#include <cstdint>
#include <cassert>
#include <iostream>

// Task 13: Подсчет установленных битов
//
// Реализуйте функцию подсчета количества установленных битов в числе.
// Нужно написать 3 версии:
// 1. Через цикл по битам
// 2. Через lookup table
// 3. Через встроенную функцию __builtin_popcount (gcc/clang) или _mm_popcnt_u32 (MSVC)
//
// Пример:
// countBits(0b1010) -> 2
// countBits(0xFF)   -> 8

// Решение через цикл
int countBitsLoop(uint32_t n) {
    // TODO: реализуйте функцию
    return 0;
}

// Решение через таблицу
// Подсказка: создайте статическую таблицу для подсчета битов в байте
int countBitsTable(uint32_t n) {
    // TODO: реализуйте функцию
    return 0;
}

// Решение через встроенную функцию
int countBitsFast(uint32_t n) {
    // TODO: реализуйте функцию используя __builtin_popcount или _mm_popcnt_u32
    return 0;
}

// Код для проверки
void testBitCounting() {
    // Тестовые значения
    const uint32_t test_values[] = {
        0,          // 0 битов
        0b1,        // 1 бит
        0b1010,     // 2 бита
        0xFF,       // 8 битов
        0xFFFFFFFF  // 32 бита
    };
    
    const int expected_counts[] = {0, 1, 2, 8, 32};
    
    // Проверка всех реализаций
    for (size_t i = 0; i < sizeof(test_values)/sizeof(test_values[0]); ++i) {
        uint32_t value = test_values[i];
        int expected = expected_counts[i];
        
        assert(countBitsLoop(value) == expected);
        assert(countBitsTable(value) == expected);
        assert(countBitsFast(value) == expected);
    }
    
    std::cout << "Bit counting tests passed!\n";
}

int main() {
    testBitCounting();
    return 0;
}
