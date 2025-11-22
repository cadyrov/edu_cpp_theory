#include <iostream>
#include <string>

// Task 1: Базовое использование битовых полей
// 
// Создайте структуру Flags, которая:
// 1. Использует всего 1 байт памяти (проверить через static_assert)
// 2. Содержит 4 булевых флага: active, ready, valid, error
// 3. Реализуйте метод print(std::ostream& out), который выводит состояние флагов:
//    active: false
//    ready: true
//    valid: false
//    error: true
//
// Проверки:
// - Размер структуры 1 байт (static_assert)
// - Корректность начального состояния (все false)
// - Установка и проверка отдельных флагов
// - Корректность вывода

struct Flags {
    // TODO: реализуйте битовые поля для 4 флагов
    // TODO: реализуйте метод print
    std::ostream& print(std::ostream& out) {
        // TODO: реализуйте
        return out;
    }
};

// Код для проверки
void testFlags() {
    static_assert(sizeof(Flags) == 1, "Flags должна занимать 1 байт!");
    
    Flags f{};
    f.print(std::cout);  // Ожидаем все флаги false
    
    // Установка флагов
    // TODO: установите флаги active и valid в true
    f.print(std::cout);  // Ожидаем active и valid в true, остальные false
}

int main() {
    testFlags();
    return 0;
}
