#include <iostream>

// Task 3: Регистр управления устройством
// 
// Реализуйте структуру DeviceControl для управления виртуальным устройством:
// 1. power: 1 бит (вкл/выкл)
// 2. mode: 2 бита (0-3: IDLE, ACTIVE, STANDBY, ERROR)
// 3. speed: 3 бита (0-7)
// 4. temperature: 4 бита (0-15)
// 5. reserved: 6 бит (зарезервировано для будущего использования)
//
// Структура должна занимать ровно 2 байта

enum class DeviceMode {
    IDLE,
    ACTIVE,
    STANDBY,
    ERROR
};

struct DeviceControl {
    // TODO: реализуйте структуру
    
    // Устанавливает скорость (0-7)
    bool setSpeed(unsigned int value) {
        // TODO: реализуйте метод
        return false;
    }
    
    // Устанавливает температуру (0-15)
    bool setTemperature(unsigned int value) {
        // TODO: реализуйте метод
        return false;
    }
    
    // Устанавливает режим работы
    void setMode(DeviceMode mode) {
        // TODO: реализуйте метод
    }
    
    // Включает/выключает устройство
    void setPower(bool on) {
        // TODO: реализуйте метод
    }
    
    // Выводит текущее состояние устройства
    void printStatus() const {
        // TODO: реализуйте метод
    }
};

// Код для проверки
void testDeviceControl() {
    static_assert(sizeof(DeviceControl) == 2, "DeviceControl должен занимать ровно 2 байта!");
    
    DeviceControl dev;
    
    // Тест базового функционала
    dev.setPower(true);
    dev.setMode(DeviceMode::ACTIVE);
    assert(dev.setSpeed(5));      // Корректное значение
    assert(dev.setTemperature(10)); // Корректное значение
    
    // Тест некорректных значений
    assert(!dev.setSpeed(8));      // Слишком большое значение
    assert(!dev.setTemperature(16)); // Слишком большое значение
    
    // Вывод состояния
    dev.printStatus();
}

int main() {
    testDeviceControl();
    return 0;
}
