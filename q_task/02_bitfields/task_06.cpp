#include <iostream>
#include <cstdint>

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
    bool carry:1;
    bool zero:1;
    bool sign:1;
    bool overflow:1;
    bool interrupt:1;
    uint8_t reserved:3;
    
public:
    // Конструктор по умолчанию (все флаги = 0)
    CPUFlags() {}
    
    // Обновление флагов после сложения
    void updateAfterAdd(uint8_t a, uint8_t b) {
        uint16_t result = static_cast<uint16_t>(a) + b;  // расширяем до 16 бит чтобы поймать carry
    
        carry = (result > 255);  // если результат больше чем может хранить uint8_t
        zero = (result & 0xFF) == 0;  // если младшие 8 бит результата = 0
        sign = (result & 0x80);  // если установлен старший бит (7-й)
        
        // overflow происходит когда:
        // - оба числа положительные, а результат отрицательный
        // - оба числа отрицательные, а результат положительный
        bool a_sign = (a & 0x80);
        bool b_sign = (b & 0x80);
        bool r_sign = (result & 0x80);
        overflow = (a_sign == b_sign) && (a_sign != r_sign);
    }
    
    // Обновление флагов после вычитания
    void updateAfterSub(uint8_t a, uint8_t b) {
        uint16_t result = static_cast<uint16_t>(a) - b;  // расширяем до 16 бит чтобы поймать carry
        
        carry = (result & 0xFF) == 0;  // если младшие 8 бит результата = 0
        zero = (result & 0xFF) == 0;  // если младшие 8 бит результата = 0
        sign = (result & 0x80);  // если установлен старший бит (7-й)
        
        // overflow происходит когда:
        // - оба числа положительные, а результат отрицательный
        // - оба числа отрицательные, а результат положительный
        bool a_sign = (a & 0x80);
        bool b_sign = (b & 0x80);
        bool r_sign = (result & 0x80);
        overflow = (a_sign == b_sign) && (a_sign != r_sign);
    }

    // Методы для условных переходов
    bool isEqual() const {
        return zero;
    }
    
    bool isLess() const {
        return sign != overflow;
    }
    
    bool isGreater() const {
        return !zero && sign == overflow;
    }
    
    // Сохранение состояния флагов
    uint8_t saveState() const {
        uint8_t state = 0;
        state |= carry ? 0x01 : 0;
        state |= zero ? 0x02 : 0;
        state |= sign ? 0x04 : 0;
        state |= overflow ? 0x08 : 0;
        state |= interrupt ? 0x10 : 0;
        state |= (reserved << 5) & 0xE0;
        return state;
    }
    
    // Восстановление состояния флагов
    void restoreState(uint8_t state) {
        // TODO: реализуйте восстановление состояния из байта
        carry = (state & 0x01);
        zero = (state & 0x02);
        sign = (state & 0x04);
        overflow = (state & 0x08);
        interrupt = (state & 0x10);
        reserved = (state & 0xE0);
    }
    
    // Вывод состояния флагов
    void printFlags() const {
        // TODO: реализуйте вывод текущего состояния всех флагов
        std::cout << "carry: " << (carry ? "true" : "false") << std::endl;
        std::cout << "zero: " << (zero ? "true" : "false") << std::endl;
        std::cout << "sign: " << (sign ? "true" : "false") << std::endl;
        std::cout << "overflow: " << (overflow ? "true" : "false") << std::endl;
        std::cout << "interrupt: " << (interrupt ? "true" : "false") << std::endl;
        std::cout << "reserved: " << (reserved ? "true" : "false") << std::endl;
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
