#include <iostream>
#include <cstdint>
#include <cassert>

// Task 6: Регистр состояния процессора
// 
// Реализуйте структуру CPUFlags, которая эмулирует регистр флагов процессора:
// - carry: 1 бит (флаг переноса)
// - zero: 1 бит (флаг нуля)
// - sign: 1 бит (флаг знака)
// - overflow: 1 бит (флаг переполнения)
// - interrupt: 1 бит (флаг прерывания)
// - reserved: 3 бита (зарезервировано)
//
// Структура должна:
// 1. Корректно обновлять флаги при арифметических операциях
// 2. Поддерживать сохранение/восстановление состояния
// 3. Иметь методы для проверки условий перехода (условные JMP)

class CPUFlags {
    // TODO: реализуйте битовые поля для флагов
    
public:
    // Конструктор по умолчанию (все флаги = 0)
    CPUFlags() {}
    
    // Обновление флагов после сложения
    void updateAfterAdd(uint8_t a, uint8_t b) {
        // TODO: реализуйте обновление флагов после сложения
    }
    
    // Обновление флагов после вычитания
    void updateAfterSub(uint8_t a, uint8_t b) {
        // TODO: реализуйте обновление флагов после вычитания
    }

    // Методы для условных переходов
    bool isEqual() const {
        // TODO: реализуйте метод
        return false;
    }
    
    bool isLess() const {
        // TODO: реализуйте метод
        return false;
    }
    
    bool isGreater() const {
        // TODO: реализуйте метод
        return false;
    }
    
    // Сохранение состояния флагов
    uint8_t saveState() const {
        // TODO: реализуйте сохранение состояния в байт
        return 0;
    }
    
    // Восстановление состояния флагов
    void restoreState(uint8_t state) {
        // TODO: реализуйте восстановление состояния из байта
    }
    
    // Вывод состояния флагов
    void printFlags() const {
        // TODO: реализуйте вывод текущего состояния всех флагов
    }
};

// Код для проверки
void testCPUFlags() {
    CPUFlags flags;
    
    // Тест сложения
    flags.updateAfterAdd(127, 1);  // Должно установить overflow
    assert(flags.isEqual() == false);
    assert(flags.isGreater() == true);
    
    // Тест вычитания
    flags.updateAfterSub(1, 1);    // Должно установить zero
    assert(flags.isEqual() == true);
    assert(flags.isLess() == false);
    
    // Тест сохранения/восстановления
    uint8_t saved_state = flags.saveState();
    flags.updateAfterAdd(255, 1);  // Изменяем состояние
    flags.restoreState(saved_state);  // Восстанавливаем
    assert(flags.isEqual() == true);  // Должно быть как после вычитания
    
    std::cout << "CPUFlags tests passed!\n";
}

int main() {
    testCPUFlags();
    return 0;
}
