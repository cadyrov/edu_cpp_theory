#include <iostream>
#include <cassert>
#include <string>

// Task 1: Определение L-value и R-value
//
// Напишите перегруженные функции identify, которые определяют тип выражения:
// - Для L-value ссылок возвращает true
// - Для R-value ссылок возвращает false
// - Для const L-value ссылок возвращает true

// Функция для обычного L-value
bool identify(int& x) {
    return true;  // это L-value
}

// Функция для R-value
bool identify(int&& x) {
    return false;  // это R-value
}

// Функция для const L-value
bool identify(const int& x) {
    return true;  // это тоже L-value (const)
}

// Код для проверки
void testIdentify() {
    int x = 42;
    const int y = 10;
    
    // Тест L-value
    assert(identify(x) == true);
    
    // Тест R-value
    assert(identify(42) == false);
    
    // Тест const L-value
    assert(identify(y) == true);
    
    // Тест R-value с std::move
    assert(identify(std::move(x)) == false);
    
    std::cout << "Identify tests passed!\n";
}

int main() {
    testIdentify();
    return 0;
}
