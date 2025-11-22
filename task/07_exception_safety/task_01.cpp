#include <iostream>
#include <cassert>
#include <memory>
#include <stdexcept>

// Task 1: Базовая гарантия exception safety
//
// Реализуйте класс SafeArray, который:
// 1. Гарантирует отсутствие утечек памяти при исключениях
// 2. Использует RAII для управления памятью
// 3. Правильно обрабатывает исключения в методах

class SafeArray {
    std::unique_ptr<int[]> data_;
    size_t size_;
    
public:
    // TODO: Конструктор (базовая гарантия)
    SafeArray(size_t size) : size_(size) {
        // TODO: выделите память через make_unique
        // TODO: при исключении память освободится автоматически
    }
    
    // TODO: Метод для установки значения (может выбросить исключение)
    void setValue(size_t index, int value) {
        // TODO: проверьте границы
        // TODO: если индекс невалидный, выбросьте std::out_of_range
        // TODO: установите значение
    }
    
    // TODO: Метод для получения значения
    int getValue(size_t index) const {
        // TODO: проверьте границы
        // TODO: если индекс невалидный, выбросьте std::out_of_range
        // TODO: верните значение
        return 0;
    }
    
    size_t getSize() const { return size_; }
};

// Код для проверки
void testBasicGuarantee() {
    // Нормальное использование
    {
        SafeArray arr(10);
        arr.setValue(0, 42);
        assert(arr.getValue(0) == 42);
        // Память освободится автоматически
    }
    
    // Тест с исключением - память не должна утечь
    {
        SafeArray arr(5);
        try {
            arr.setValue(10, 100);  // Выход за границы
            assert(false);  // Не должно дойти сюда
        } catch (const std::out_of_range& e) {
            // Исключение поймано, память должна быть освобождена
        }
        // Проверка что массив все еще валиден
        assert(arr.getSize() == 5);
    }
    
    // Тест чтения с невалидным индексом
    {
        SafeArray arr(3);
        try {
            arr.getValue(5);
            assert(false);
        } catch (const std::out_of_range& e) {
            // Ожидаемое исключение
        }
    }
    
    std::cout << "Basic guarantee tests passed!\n";
}

int main() {
    testBasicGuarantee();
    return 0;
}

