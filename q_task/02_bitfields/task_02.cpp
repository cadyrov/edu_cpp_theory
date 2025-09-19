#include <cstdint>
#include <iostream>

// Task 2: RGB Color
// 
// Реализуйте структуру RGBColor, которая:
// 1. Хранит компоненты RGB (red, green, blue) по 8 бит каждый
// 2. Имеет методы для установки и получения компонентов
// 3. Проверяет, что значения не превышают 255
// 4. Занимает минимально возможный размер в памяти
//
// Примечание: используйте битовые поля для оптимизации памяти

struct RGBColor {
    static constexpr unsigned int max_val = 255;

    uint8_t red=0;
    uint8_t green=0;
    uint8_t blue=0;
    
    // Методы установки значений должны проверять диапазон
    bool setRed(unsigned int value) {
        if (value > max_val) {
            return false;
        }

        red = value;

        return true;
    }
    
    bool setGreen(unsigned int value){
        if (value > max_val) {
            return false;
        }

        green = value;

        return true;
    }
    
    bool setBlue(unsigned int value) {
         if (value > max_val) {
            return false;
        }

        blue = value;

        return true;
    }
    
    // Геттеры
    unsigned int getRed() const {
        return red;
    }
    
    unsigned int getGreen() const {
        return green;
    }
    
    unsigned int getBlue() const {
        return blue;
    }
};

// Код для проверки
void testRGBColor() {
    RGBColor color;
    
    // Проверка установки корректных значений
    assert(color.setRed(255));
    assert(color.setGreen(128));
    assert(color.setBlue(64));
    
    // Проверка получения значений
    assert(color.getRed() == 255);
    assert(color.getGreen() == 128);
    assert(color.getBlue() == 64);
    
    // Проверка установки некорректных значений
    assert(!color.setRed(256));    // Слишком большое значение
    assert(!color.setGreen(300));  // Слишком большое значение
    assert(!color.setBlue(999));   // Слишком большое значение
    
    // Значения не должны измениться
    assert(color.getRed() == 255);
    assert(color.getGreen() == 128);
    assert(color.getBlue() == 64);
    
    // Проверка размера структуры
    std::cout << "Size of RGBColor: " << sizeof(RGBColor) << " bytes\n";
    // Ожидаем размер 3 или 4 байта (зависит от выравнивания)
}

int main() {
    testRGBColor();
    return 0;
}
