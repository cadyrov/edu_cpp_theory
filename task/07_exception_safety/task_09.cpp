#include <iostream>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <vector>

// Task 9: Обработка исключений в конструкторах
//
// Реализуйте класс SafeConstructor, который:
// 1. Правильно обрабатывает исключения в конструкторе
// 2. Гарантирует что частично созданный объект не останется
// 3. Использует RAII для всех членов

class Part {
    int value_;
public:
    Part(int v) : value_(v) {
        if (v < 0) {
            throw std::invalid_argument("Negative value");
        }
    }
    int getValue() const { return value_; }
};

class SafeConstructor {
    std::unique_ptr<Part> part1_;
    std::unique_ptr<Part> part2_;
    std::vector<int> data_;
    
public:
    // TODO: Конструктор с обработкой исключений
    SafeConstructor(int v1, int v2, size_t data_size) {
        // TODO: создайте part1_ через make_unique
        // TODO: если создание part1_ успешно, создайте part2_
        // TODO: если создание part2_ успешно, инициализируйте data_
        // TODO: при любом исключении все уже созданные члены автоматически освободятся
    }
    
    // TODO: Конструктор с валидацией
    SafeConstructor(const std::vector<int>& values) {
        // TODO: проверьте что values не пустой
        // TODO: если пустой, выбросьте std::invalid_argument
        // TODO: инициализируйте data_ копированием values
        // TODO: создайте part1_ и part2_ на основе данных
    }
    
    bool isValid() const {
        return part1_ != nullptr && part2_ != nullptr && !data_.empty();
    }
    
    size_t getDataSize() const { return data_.size(); }
};

// Код для проверки
void testConstructorExceptions() {
    // Нормальное создание
    {
        SafeConstructor obj(10, 20, 5);
        assert(obj.isValid());
        assert(obj.getDataSize() == 5);
    }
    
    // Тест с исключением при создании part1
    try {
        SafeConstructor obj(-1, 20, 5);  // part1 выбросит исключение
        assert(false);
    } catch (const std::invalid_argument& e) {
        // Исключение поймано, объект не создан
    }
    
    // Тест с исключением при создании part2
    try {
        SafeConstructor obj(10, -20, 5);  // part2 выбросит исключение
        assert(false);
    } catch (const std::invalid_argument& e) {
        // part1 должен быть автоматически освобожден
    }
    
    // Тест с пустым вектором
    try {
        SafeConstructor obj(std::vector<int>{});  // Пустой вектор
        assert(false);
    } catch (const std::invalid_argument& e) {
        // Исключение поймано
    }
    
    // Тест успешного создания из вектора
    {
        SafeConstructor obj(std::vector<int>{1, 2, 3, 4, 5});
        assert(obj.isValid());
        assert(obj.getDataSize() == 5);
    }
    
    std::cout << "Constructor exception handling tests passed!\n";
}

int main() {
    testConstructorExceptions();
    return 0;
}

