#include <iostream>
#include <cassert>
#include <string>

// Task 1: Определение L-value и R-value
//
// Напишите функции которые определяют тип выражения:
// - isLValue() - возвращает true если аргумент L-value
// - isRValue() - возвращает true если аргумент R-value
//
// Используйте перегрузку функций для определения типа

// Функция для L-value
void identify(int& x) {
    // TODO: реализуйте
}

// Функция для R-value
void identify(int&& x) {
    // TODO: реализуйте
}

// Функция для const L-value
void identify(const int& x) {
    // TODO: реализуйте
}

// Код для проверки
void testIdentify() {
    int x = 42;
    const int y = 10;
    
    // TODO: добавьте тесты
    
    std::cout << "Identify tests passed!\n";
}

int main() {
    testIdentify();
    return 0;
}
