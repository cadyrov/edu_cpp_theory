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
    // TODO: реализуйте структуру
    
    // Методы установки значений должны проверять диапазон
    bool setRed(unsigned int value) {
        // TODO: реализуйте метод
        return false;
    }
    
    bool setGreen(unsigned int value) {
        // TODO: реализуйте метод
        return false;
    }
    
    bool setBlue(unsigned int value) {
        // TODO: реализуйте метод
        return false;
    }
    
    // Геттеры
    unsigned int getRed() const {
        // TODO: реализуйте метод
        return 0;
    }
    
    unsigned int getGreen() const {
        // TODO: реализуйте метод
        return 0;
    }
    
    unsigned int getBlue() const {
        // TODO: реализуйте метод
        return 0;
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
