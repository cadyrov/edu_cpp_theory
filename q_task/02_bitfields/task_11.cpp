#include <cstdint>

// Task 11: Упаковка RGB в одно число
// 
// Реализуйте функции packRGB и unpackRGB:
// - packRGB(r,g,b) -> упаковывает 3 байта RGB в одно 32-битное число
// - unpackRGB(color) -> возвращает структуру с отдельными компонентами RGB
//
// Пример:
// packRGB(255, 128, 0)   -> 0x00FF8000
// unpackRGB(0x00FF8000)  -> {r: 255, g: 128, b: 0}

struct RGB {
    uint8_t r, g, b;
};

// Упаковывает RGB компоненты в одно 32-битное число
uint32_t packRGB(uint8_t r, uint8_t g, uint8_t b) {
    // TODO: реализуйте функцию
    return 0;
}

// Распаковывает 32-битное число в структуру RGB
RGB unpackRGB(uint32_t color) {
    // TODO: реализуйте функцию
    return {0, 0, 0};
}

// Код для проверки
void testRGBPacking() {
    // Тест упаковки
    uint32_t packed = packRGB(255, 128, 0);
    assert(packed == 0x00FF8000);
    
    // Тест распаковки
    RGB unpacked = unpackRGB(packed);
    assert(unpacked.r == 255);
    assert(unpacked.g == 128);
    assert(unpacked.b == 0);
    
    // Тест граничных значений
    packed = packRGB(0, 0, 0);
    unpacked = unpackRGB(packed);
    assert(unpacked.r == 0 && unpacked.g == 0 && unpacked.b == 0);
    
    packed = packRGB(255, 255, 255);
    unpacked = unpackRGB(packed);
    assert(unpacked.r == 255 && unpacked.g == 255 && unpacked.b == 255);
    
    std::cout << "RGB packing tests passed!\n";
}

int main() {
    testRGBPacking();
    return 0;
}
