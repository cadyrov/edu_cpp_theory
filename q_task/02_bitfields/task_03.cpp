#include <cstdint>
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
    ERROR,
};

uint8_t toUint8(DeviceMode mode) {
    return static_cast<uint8_t>(mode);
}

std::string ToString(DeviceMode mode) {
    switch (mode) {
        case DeviceMode::IDLE:
            return "IDLE";
        case DeviceMode::ACTIVE:
            return "ACTIVE";
        case DeviceMode::STANDBY:
            return "STANDBY";
        case DeviceMode::ERROR:
            return "ERROR";    
    }
}

DeviceMode ToDeviceMode(uint8_t mode) {
    return static_cast<DeviceMode>(mode);
}


struct DeviceControl {
    uint8_t reserved_:6;
    uint8_t mode_:2;
    uint8_t temperature_:4;
    uint8_t speed_:3;
    bool power_:1;
    
    
 
    // Устанавливает скорость (0-7)
    bool setSpeed(unsigned int value) {
        if (value > 7) {
            return false;
        }
        
        speed_ = value;

        return true;
    }
    
    // Устанавливает температуру (0-15)
    bool setTemperature(unsigned int value) {
        if (value > 15) {
            return false;
        }
        
        temperature_ = value;

        return true;
    }
    
    // Устанавливает режим работы
    void setMode(DeviceMode mode) {
        mode_ = toUint8(mode);
    }
    
    // Включает/выключает устройство
    void setPower(bool on) {
       power_ = on;
    }
    
    // Выводит текущее состояние устройства
    friend std::ostream& operator<<(std::ostream& out, const DeviceControl& dc) {
        out << "power: " << dc.power_ << 
            ", mode: "<< ToString(ToDeviceMode(dc.mode_))<<
            ", speed: "<< dc.speed_ <<
            ", temperature: "<< dc.temperature_;
    
        return out;
    };
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
    std::cout << dev;
}

int main() {
    testDeviceControl();
    return 0;
}
