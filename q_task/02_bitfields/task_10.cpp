#include <iostream>
#include <cstdint>

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
    // TODO: реализуйте структуры для хранения регистров
    
public:
    ProcessorEmulator() {
        // TODO: реализуйте инициализацию процессора
    }
    
    // Методы доступа к регистрам общего назначения
    bool setRegister(uint8_t reg, uint32_t value) {
        // TODO: реализуйте установку значения регистра
        return false;
    }
    
    uint32_t getRegister(uint8_t reg) const {
        // TODO: реализуйте получение значения регистра
        return 0;
    }
    
    // Методы управления режимом процессора
    bool setMode(ProcessorMode mode) {
        // TODO: реализуйте смену режима с проверкой привилегий
        return false;
    }
    
    ProcessorMode getMode() const {
        // TODO: реализуйте получение текущего режима
        return ProcessorMode::USER;
    }
    
    // Методы управления прерываниями
    void enableInterrupts(bool enable) {
        // TODO: реализуйте включение/выключение прерываний
    }
    
    bool areInterruptsEnabled() const {
        // TODO: реализуйте проверку состояния прерываний
        return false;
    }
    
    // Методы управления кэшем
    void enableCache(bool enable) {
        // TODO: реализуйте включение/выключение кэша
    }
    
    bool isCacheEnabled() const {
        // TODO: реализуйте проверку состояния кэша
        return false;
    }
    
    // Установка количества стадий конвейера
    bool setPipelineStages(uint8_t stages) {
        // TODO: реализуйте установку количества стадий (1-7)
        return false;
    }
    
    uint8_t getPipelineStages() const {
        // TODO: реализуйте получение количества стадий
        return 0;
    }
    
    // Эмуляция инструкций
    void executeAdd(uint8_t rd, uint8_t rn, uint8_t rm) {
        // TODO: реализуйте операцию сложения регистров
    }
    
    void executeSub(uint8_t rd, uint8_t rn, uint8_t rm) {
        // TODO: реализуйте операцию вычитания регистров
    }
    
    void executeMove(uint8_t rd, uint8_t rm) {
        // TODO: реализуйте операцию перемещения данных между регистрами
    }
    
    // Бонус: Обработка прерываний
    void handleInterrupt(uint8_t vector) {
        // TODO: реализуйте обработку прерывания
    }
    
    // Вывод состояния процессора
    void printState() const {
        // TODO: реализуйте вывод состояния всех регистров и флагов
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
    proc.printState();
}

int main() {
    testProcessor();
    return 0;
}
