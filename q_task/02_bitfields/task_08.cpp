#include <iostream>
#include <cstdint>

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

std::ostream& operator << (std::ostream& out,const ColorMode& data ) {
    switch (data) {
        case ColorMode::MONO:
            out << "MONO";
            break; 
        case ColorMode::GRAY_4:
            out << "GRAY_4";
            break; 
        case ColorMode::GRAY_16:
            out << "GRAY_16";
            break; 
        case ColorMode::RGB_222:
            out << "RGB_222";
            break; 
        case ColorMode::RGB_565:
            out << "RGB_565";
            break; 
        case ColorMode::RGB_888:
            out << "RGB_888";
            break;
        default:
            out << "UNKNOWN"; 
    }

    return out;
}


enum class Orientation{
    ANG_0 = 0,
    ANG_90 = 1,
    ANG_180 = 2,
    ANG_270 = 3,
};

std::ostream& operator << (std::ostream& out,const Orientation& data ) {
    switch (data) {
        case Orientation::ANG_0:
            out << "0°";
            break; 
        case Orientation::ANG_90:
            out << "90°";
            break; 
        case Orientation::ANG_180:
            out << "180°";
            break; 
        case Orientation::ANG_270:
            out << "270°";
            break; 
        default:
            out << "UNKNOWN"; 
    }

    return out;
}

class LCDControl {
    uint8_t contrast_:4;
    uint8_t brightness_:4;
    uint8_t color_mode_:3;
    uint8_t power_:1;
    uint8_t orientation_:2;
    uint8_t reserved_:2;
    // TODO: реализуйте структуру для хранения регистра управления
    
public:
    // Конструктор по умолчанию
    LCDControl() {}
    
    // Методы управления питанием
    void setPower(bool on) {
        power_ = on;
    }
    
    bool isPowered() const {
        return power_;
    }
    
    // Методы управления яркостью
    bool setBrightness(uint8_t level) {
        if (level >15) {
            return false;
        }

        brightness_ = level;

        return true;
    }
    
    uint8_t getBrightness() const {
        return brightness_;
    }
    
    // Методы управления контрастом
    bool setContrast(uint8_t level) {
        if (level >15) {
            return false;
        }
        contrast_ = level;

        return true;
    }
    
    uint8_t getContrast() const {
        return contrast_;
    }
    
    // Методы управления ориентацией
    bool setOrientation(uint8_t angle) {
        if (angle > 3) {
            return false;
        }

        orientation_ = angle;

        return true;
    }
    
    uint8_t getOrientation() const {
        return orientation_;
    }
    
    // Методы управления цветовым режимом
    bool setColorMode(ColorMode mode) {
        color_mode_ = static_cast<uint8_t>(mode);

        return true;
    }
    
    ColorMode getColorMode() const {
        return static_cast<ColorMode>(color_mode_);
    }
    

    // Сохранение конфигурации
    uint16_t saveConfig() const {
        uint16_t result = 0;
        result |= contrast_ << 0;
        result |= brightness_ << 4;
        result |= color_mode_ << 8;
        result |= power_ << 11;
        result |= orientation_ << 12;
        result |= reserved_ << 14;

        // TODO: реализуйте сохранение конфигурации в 16-битное число
        return result;
    }
    
    // Загрузка конфигурации
    void loadConfig(uint16_t config) {
        contrast_ = config & 0x0F;
        brightness_ = (config >> 4) & 0x0F;
        color_mode_ = (config >> 8) & 0x07;
        power_ = (config >> 11) & 0x01;
        orientation_ = (config >> 12) & 0x03;
        reserved_ = (config >> 14) & 0x03;
    }
    
    // Бонус: Анимация изменения яркости
    void animateBrightness(uint8_t target_level, unsigned int steps = 10) {
        // TODO: реализуйте плавное изменение яркости
    }
    
    // Вывод текущей конфигурации
    friend std::ostream& operator << (std::ostream& out,const LCDControl& data ) {
        out << "contrast: " << data.contrast_ <<  " " <<
            "brightness: " << data.brightness_ <<  " " <<
            "color_mode: " << data.getColorMode() <<  " " <<
            "power: " << (data.power_? "ON":"OFF") << " " <<
            "orientation: " << static_cast<Orientation>(data.orientation_) <<" " <<
            "reserved: " << data.reserved_;

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
    lcd.printConfig();
}

int main() {
    testLCDControl();
    return 0;
}
