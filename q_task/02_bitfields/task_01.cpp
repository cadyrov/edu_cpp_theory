#include <iostream>

// Task 1: Базовое использование битовых полей
// 
// Создайте структуру Flags, которая:
// 1. Использует всего 1 байт памяти
// 2. Содержит 4 булевых флага: active, ready, valid, error
// 3. Реализуйте метод printFlags() для вывода состояния флагов
//
// Примечание: используйте static_assert для проверки размера структуры

struct Flags {
    // TODO: реализуйте структуру
    
    void printFlags() const {
        // TODO: реализуйте вывод состояния флагов
    }
};

// Код для проверки
void testFlags() {
    static_assert(sizeof(Flags) == 1, "Flags должна занимать 1 байт!");
    
    Flags f{};
    f.printFlags();  // Ожидаем: все флаги false
    
    // Установка флагов
    f.active = true;
    f.valid = true;
    f.printFlags();  // Ожидаем: active и valid true, остальные false
}

int main() {
    testFlags();
    return 0;
}
