#include <iostream>
#include <cstdint>
#include <ostream>
#include <cassert>

// Task 10: Эмулятор регистров процессора
// 
// Реализуйте класс ProcessorEmulator, который эмулирует работу с регистрами процессора:
// 1. Регистры общего назначения (R0-R7, 32 бита каждый)
// 2. Регистр флагов (как в задаче 6)
// 3. Регистр управления:
//    - mode: 2 бита (USER=0, SUPERVISOR=1, INTERRUPT=2, ERROR=3)
//    - interrupt_enable: 1 бит
//    - cache_enable: 1 бит
//    - pipeline_stages: 3 бита (1-7)
//    - reserved: 1 бит
// 4. Поддержка базовых операций процессора
// 5. Корректная обработка привилегий и режимов
//
// Бонус: Реализуйте простой механизм прерываний

enum class ProcessorMode {
    USER = 0,
    SUPERVISOR = 1,
    INTERRUPT = 2,
    ERROR = 3
};

class ProcessorEmulator {
private:
    // TODO: реализуйте регистры общего назначения
    // TODO: реализуйте регистр управления с битовыми полями
    
public:
    ProcessorEmulator() {}
    
    // Методы доступа к регистрам общего назначения
    bool setRegister(uint8_t reg, uint32_t value) {
        // TODO: реализуйте метод
        return false;
    }
    
    uint32_t getRegister(uint8_t reg) const {
        // TODO: реализуйте метод
        return 0;
    }
    
    // Методы управления режимом процессора
    bool setMode(ProcessorMode mode) {
        // TODO: реализуйте метод с проверкой привилегий
        return false;
    }
    
    ProcessorMode getMode() const {
        // TODO: реализуйте метод
        return ProcessorMode::USER;
    }
    
    // Методы управления прерываниями
    void enableInterrupts(bool enable) {
        // TODO: реализуйте метод
    }
    
    bool areInterruptsEnabled() const {
        // TODO: реализуйте метод
        return false;
    }
    
    // Методы управления кэшем
    void enableCache(bool enable) {
        // TODO: реализуйте метод
    }
    
    bool isCacheEnabled() const {
        // TODO: реализуйте метод
        return false;
    }
    
    // Установка количества стадий конвейера
    bool setPipelineStages(uint8_t stages) {
        // TODO: реализуйте метод
        return false;
    }
    
    uint8_t getPipelineStages() const {
        // TODO: реализуйте метод
        return 0;
    }
    
    // Эмуляция инструкций
    void executeAdd(uint8_t rd, uint8_t rn, uint8_t rm) {
        // TODO: реализуйте инструкцию сложения
    }
    
    void executeSub(uint8_t rd, uint8_t rn, uint8_t rm) {
        // TODO: реализуйте инструкцию вычитания
    }
    
    void executeMove(uint8_t rd, uint8_t rm) {
        // TODO: реализуйте инструкцию перемещения
    }
    
    // Бонус: Обработка прерываний
    void handleInterrupt(uint8_t vector) {
        // TODO: реализуйте обработку прерываний
    }
    

    friend std::ostream& operator << (std::ostream& out, const ProcessorEmulator& data) {
        // TODO: реализуйте вывод состояния процессора
        return out;
    }
};

// Код для проверки
void testProcessor() {
    ProcessorEmulator proc;
    
    // Тест регистров общего назначения
    assert(proc.setRegister(0, 42));
    assert(proc.setRegister(1, 24));
    assert(proc.getRegister(0) == 42);
    assert(!proc.setRegister(8, 1));  // Некорректный номер регистра
    
    // Тест режимов процессора
    assert(proc.getMode() == ProcessorMode::USER);
    assert(!proc.setMode(ProcessorMode::SUPERVISOR));  // Нельзя повысить привилегии
    
    // Тест управления прерываниями
    proc.enableInterrupts(true);
    assert(proc.areInterruptsEnabled());
    
    // Тест конвейера
    assert(proc.setPipelineStages(5));
    assert(!proc.setPipelineStages(8));  // Некорректное значение
    assert(proc.getPipelineStages() == 5);
    
    // Тест инструкций
    proc.executeAdd(2, 0, 1);  // R2 = R0 + R1
    assert(proc.getRegister(2) == 66);  // 42 + 24
    
    std::cout << "ProcessorEmulator tests passed!\n";
    std::cout << proc;
}

int main() {
    testProcessor();
    return 0;
}
