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

std::ostream& operator << (std::ostream& out, const ProcessorMode mode) {
    out << "ProcessorMode: ";
    switch (mode) {
        case ProcessorMode::USER:
            out << "USER";
            break;
        case ProcessorMode::SUPERVISOR:
            out << "SUPERVISOR";
            break;
        case ProcessorMode::INTERRUPT:
            out << "INTERRUPT";
            break;
        case ProcessorMode::ERROR:
            out << "ERROR";
            break;
        default:
            out << "UNKNOWN";
    }

    return out;
}

class ProcessorEmulator {
private:
    uint32_t common_[8]= {};
    uint8_t pipeline_stages_:3;
    uint8_t mode_:2;
    uint8_t interrupt_enable_:1;
    uint8_t cache_enable_:1;
    uint8_t reserved_:1;
public:
    ProcessorEmulator():pipeline_stages_(1),mode_(0),interrupt_enable_(0),cache_enable_(0),reserved_(0) {}
    
    // Методы доступа к регистрам общего назначения
    bool setRegister(uint8_t reg, uint32_t value) {
        if (reg > 7) {
            return false;
        }

        common_[reg] = value;

        return true;
    }
    
    uint32_t getRegister(uint8_t reg) const {
        if (reg > 7) {
            return 0;
        }

        return common_[reg];
    }
    
    // Методы управления режимом процессора
    bool setMode(ProcessorMode mode) {
        if (mode > ProcessorMode::ERROR) {
            return false;
        }

        if (getMode() == ProcessorMode::USER && mode > ProcessorMode::USER) { 
            return false;
        }

        mode_ = static_cast<uint8_t>(mode);

        return true;
    }
    
    ProcessorMode getMode() const {
        return static_cast<ProcessorMode>(mode_);
    }
    
    // Методы управления прерываниями
    void enableInterrupts(bool enable) {
        interrupt_enable_ = enable;
    }
    
    bool areInterruptsEnabled() const {
        return interrupt_enable_;
    }
    
    // Методы управления кэшем
    void enableCache(bool enable) {
        cache_enable_ = enable;
    }
    
    bool isCacheEnabled() const {
        return cache_enable_;
    }
    
    // Установка количества стадий конвейера
    bool setPipelineStages(uint8_t stages) {
        if (stages < 1 || stages > 7) {
            return false;
        }
        
        pipeline_stages_ = stages;

        return true;
    }
    
    uint8_t getPipelineStages() const {
        return pipeline_stages_;
    }
    
    // Эмуляция инструкций
    void executeAdd(uint8_t rd, uint8_t rn, uint8_t rm) {
        if (rd > 7 || rn > 7 || rm > 7) {
            return;
        }

        common_[rd] = common_[rn] + common_[rm];
    }
    
    void executeSub(uint8_t rd, uint8_t rn, uint8_t rm) {
        if (rd > 7 || rn > 7 || rm > 7) {
            return;
        }

        common_[rd] = common_[rn] - common_[rm];
    }
    
    void executeMove(uint8_t rd, uint8_t rm) {
        if (rd > 7  || rm > 7) {
            return;
        }

        common_[rd] = common_[rm];
    }
    
    // Бонус: Обработка прерываний
    void handleInterrupt(uint8_t vector) {
        if (!interrupt_enable_) {
            return; // прерывания запрещены
        }
        
        // сохраняем текущий режим
        auto old_mode = getMode();
        
        // переключаемся в режим прерывания
        setMode(ProcessorMode::INTERRUPT);
        
        // тут какая-то обработка в зависимости от vector

        switch (vector) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
        }
        // возвращаемся в предыдущий режим
        setMode(old_mode);
    }
    

    friend std::ostream& operator << (std::ostream& out, const ProcessorEmulator& data) {
        out << "registers: \n";
        for (int i = 0; i < 8; i++) {
            out << "R" << i << ": " << data.common_[i] << "\n";
        }
        out << "mode: " << data.getMode() << "\n";
        out << "interrupt_enable: " << data.interrupt_enable_ << "\n";
        out << "cache_enable: " << data.cache_enable_ << "\n";
        out << "reserved: " << data.reserved_ << "\n";
        out << "pipeline_stages: " << data.pipeline_stages_ << "\n";

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
