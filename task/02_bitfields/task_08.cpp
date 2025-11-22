#include <iostream>
#include <cstdint>
#include <cassert>

// Task 8: Регистр управления LCD дисплеем
// 
// Реализуйте структуру LCDControl для управления LCD дисплеем:
// 1. Регистр управления (16 бит):
//    - power: 1 бит (вкл/выкл)
//    - brightness: 4 бита (0-15)
//    - contrast: 4 бита (0-15)
//    - orientation: 2 бита (0=0°, 1=90°, 2=180°, 3=270°)
//    - color_mode: 3 бита (различные цветовые режимы)
//    - reserved: 2 бита
// 2. Реализуйте методы управления с проверкой значений
// 3. Добавьте поддержку сохранения/загрузки конфигурации
//
// Бонус: Реализуйте анимацию изменения яркости/контраста

enum class ColorMode {
    MONO = 0,
    GRAY_4 = 1,
    GRAY_16 = 2,
    RGB_222 = 3,
    RGB_565 = 4,
    RGB_888 = 5
};

enum class Orientation{
    ANG_0 = 0,
    ANG_90 = 1,
    ANG_180 = 2,
    ANG_270 = 3,
};

class LCDControl {
    // TODO: реализуйте структуру для хранения регистра управления
    
public:
    // Конструктор по умолчанию
    LCDControl() {}
    
    // Методы управления питанием
    void setPower(bool on) {
        // TODO: реализуйте метод
    }
    
    bool isPowered() const {
        // TODO: реализуйте метод
        return false;
    }
    
    // Методы управления яркостью
    bool setBrightness(uint8_t level) {
        // TODO: реализуйте метод
        return false;
    }
    
    uint8_t getBrightness() const {
        // TODO: реализуйте метод
        return 0;
    }
    
    // Методы управления контрастом
    bool setContrast(uint8_t level) {
        // TODO: реализуйте метод
        return false;
    }
    
    uint8_t getContrast() const {
        // TODO: реализуйте метод
        return 0;
    }
    
    // Методы управления ориентацией
    bool setOrientation(uint8_t angle) {
        // TODO: реализуйте метод
        return false;
    }
    
    uint8_t getOrientation() const {
        // TODO: реализуйте метод
        return 0;
    }
    
    // Методы управления цветовым режимом
    bool setColorMode(ColorMode mode) {
        // TODO: реализуйте метод
        return false;
    }
    
    ColorMode getColorMode() const {
        // TODO: реализуйте метод
        return ColorMode::MONO;
    }
    

    // Сохранение конфигурации
    uint16_t saveConfig() const {
        // TODO: реализуйте сохранение конфигурации в 16-битное число
        return 0;
    }
    
    // Загрузка конфигурации
    void loadConfig(uint16_t config) {
        // TODO: реализуйте загрузку конфигурации из 16-битного числа
    }
    
    // Бонус: Анимация изменения яркости
    void animateBrightness(uint8_t target_level, unsigned int steps = 10) {
        // TODO: реализуйте плавное изменение яркости
    }
    
    // Вывод текущей конфигурации
    friend std::ostream& operator << (std::ostream& out,const LCDControl& data ) {
        // TODO: реализуйте вывод
        return out;
    }
};

// Код для проверки
void testLCDControl() {
    LCDControl lcd;
    
    // Тест управления питанием
    lcd.setPower(true);
    assert(lcd.isPowered() == true);
    
    // Тест установки яркости
    assert(lcd.setBrightness(10) == true);
    assert(lcd.setBrightness(16) == false);  // некорректное значение
    assert(lcd.getBrightness() == 10);
    
    // Тест установки контраста
    assert(lcd.setContrast(8) == true);
    assert(lcd.setContrast(20) == false);  // некорректное значение
    assert(lcd.getContrast() == 8);
    
    // Тест установки ориентации
    assert(lcd.setOrientation(1) == true);  // 90°
    assert(lcd.setOrientation(4) == false); // некорректное значение
    assert(lcd.getOrientation() == 1);
    
    // Тест установки цветового режима
    assert(lcd.setColorMode(ColorMode::RGB_565) == true);
    assert(lcd.getColorMode() == ColorMode::RGB_565);
    
    // Тест сохранения/загрузки конфигурации
    uint16_t saved_config = lcd.saveConfig();
    lcd.setPower(false);
    lcd.setBrightness(0);
    lcd.loadConfig(saved_config);
    assert(lcd.isPowered() == true);
    assert(lcd.getBrightness() == 10);
    
    std::cout << "LCDControl tests passed!\n";
    
    // Демонстрация анимации (опционально)
    lcd.animateBrightness(15);
}

int main() {
    testLCDControl();
    return 0;
}
