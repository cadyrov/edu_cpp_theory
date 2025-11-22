#include <cstddef>
#include <iostream>
#include <cstdint>
#include <vector>
#include <cassert>

// Task 9: Компактный массив флагов
// 
// Реализуйте класс BitArray для эффективного хранения массива булевых значений:
// 1. Использует битовые поля для минимизации памяти
// 2. Поддерживает операции установки/получения значений по индексу
// 3. Реализует базовые битовые операции (AND, OR, XOR, NOT)
// 4. Имеет методы подсчета установленных битов
// 5. Поддерживает итерацию по установленным битам
//
// Бонус: Реализуйте операторы для удобной работы с массивом

class BitArray {
private:
    // TODO: реализуйте внутреннее представление данных
    // Подсказка: используйте std::vector<uint32_t> для хранения блоков
    
public:
    // Конструктор с указанием размера (в битах)
    explicit BitArray(size_t size) {
        // TODO: реализуйте конструктор
    }
    
    // Установка бита по индексу
    bool set(size_t index, bool value = true) {
        // TODO: реализуйте метод
        return false;
    }
    
    // Получение значения бита
    bool get(size_t index) const {
        // TODO: реализуйте получение значения бита
        return false;
    }
    
    // Инвертирование бита
    bool flip(size_t index) {
        // TODO: реализуйте инвертирование бита
        return false;
    }
    
    // Подсчет количества установленных битов
    size_t count() const {
        // TODO: реализуйте подсчет единичных битов
        return 0;
    }
    
    // Очистка всех битов
    void clear() {
        // TODO: реализуйте очистку массива
    }
    
    // Получение размера в битах
    size_t size() const {
        // TODO: реализуйте метод
        return 0;
    }
    
    // Операция AND с другим BitArray
    BitArray& operator&=(const BitArray& other) {
        // TODO: реализуйте побитовое И
        return *this;
    }
    
    // Операция OR с другим BitArray
    BitArray& operator|=(const BitArray& other) {
        // TODO: реализуйте побитовое ИЛИ
        return *this;
    }
    
    // Операция XOR с другим BitArray
    BitArray& operator^=(const BitArray& other) {
        // TODO: реализуйте побитовое исключающее ИЛИ
        return *this;
    }
    
    // Операция NOT
    BitArray operator~() const {
        // TODO: реализуйте побитовое НЕ
        return BitArray(0);
    }
    
    // Оператор доступа к биту (опционально)
    class BitReference {
        // TODO: реализуйте прокси-класс для доступа к отдельным битам
    };
    
    // TODO: реализуйте оператор доступа к биту
    // BitReference operator[](size_t index) {
    //     return BitReference(*this, index);
    // }
    
    // Вывод содержимого массива
    void print() const {
        // TODO: реализуйте вывод битов
    }
};

// Код для проверки
void testBitArray() {
    BitArray arr(100);  // 100 бит
    
    // Тест установки/получения битов
    arr.set(10, true);
    arr.set(20, true);
    arr.set(30, true);
    assert(arr.get(10) == true);
    assert(arr.get(11) == false);
    
    // Тест подсчета битов
    assert(arr.count() == 3);
    
    // Тест инвертирования
    arr.flip(10);
    assert(arr.get(10) == false);
    assert(arr.count() == 2);
    
    // Тест операций с другим массивом
    BitArray arr2(100);
    arr2.set(20, true);
    arr2.set(40, true);
    
    arr &= arr2;  // После AND должен остаться только бит 20
    assert(arr.count() == 1);
    assert(arr.get(20) == true);
    assert(arr.get(30) == false);
    
    // Тест оператора доступа (если реализован)
    // arr[50] = true;
    // assert(arr[50] == true);
    
    std::cout << "BitArray tests passed!\n";
    arr.print();
}

int main() {
    testBitArray();
    return 0;
}
