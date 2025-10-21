#include <cstddef>
#include <iostream>
#include <cstdint>
#include <vector>

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
    std::vector<uint32_t> data_;
    size_t size_=0;
    
public:
    // Конструктор с указанием размера (в битах)
    explicit BitArray(size_t size):size_(size) {
        if (size_ == 0) {
            return;
        }

        data_.resize(size/32 + 1);      
    }
    
    // Установка бита по индексу
    bool set(size_t index, bool value = true) {
        if (index >= size_){
            return false;
        }

        data_[index/32] |= (value ? 1 << index%32 : ~(1 << index%32));

        return true;
    }
    
    // Получение значения бита
    bool get(size_t index) const {
        // TODO: реализуйте получение значения бита
        return (data_[index/32] & (1 << index%32)) != 0;
    }
    
    // Инвертирование бита
    bool flip(size_t index) {
        // TODO: реализуйте инвертирование бита
        return set(index, !get(index));
    }
    
    // Подсчет количества установленных битов
    size_t count() const {
        // TODO: реализуйте подсчет единичных битов
        size_t count = 0;
        for (size_t i = 0; i < size_; i++) {
            if (get(i)) {
                count++;
            }
        }
        return count;
    }
    
    // Очистка всех битов
    void clear() {
        // TODO: реализуйте очистку массива
        data_.clear();
        data_.resize(size_/32 + 1);
    }
    
    // Получение размера в битах
    size_t size() const {
        return size_;
    }
    
    // Операция AND с другим BitArray
    BitArray& operator&=(const BitArray& other) {
        // TODO: реализуйте побитовое И
        for (size_t i = 0; i < size_; i++) {
            if (other.get(i)) {
                set(i, true);
            } else {
                set(i, false);
            }
        }
        return *this;
    }
    
    // Операция OR с другим BitArray
    BitArray& operator|=(const BitArray& other) {
        // TODO: реализуйте побитовое ИЛИ
        for (size_t i = 0; i < size_; i++) {
            if (other.get(i)) {
                set(i, true);
            } else {
                set(i, false);
            }
        }
        return *this;
    }
    
    // Операция XOR с другим BitArray
    BitArray& operator^=(const BitArray& other) {
        // TODO: реализуйте побитовое исключающее ИЛИ
        for (size_t i = 0; i < size_; i++) {
            if (other.get(i)) {
                set(i, !get(i));
            }
        }
        return *this;
    }
    
    // Операция NOT
    BitArray operator~() const {
        // TODO: реализуйте побитовое НЕ
        BitArray result(size_);
        for (size_t i = 0; i < size_; i++) {
            result.set(i, !get(i));
        }
        return result;
    }
    
    // Оператор доступа к биту (опционально)
    class BitReference {
        // TODO: реализуйте прокси-класс для доступа к отдельным битам
            BitArray& array_;
            size_t index_;
        public:
            BitReference(BitArray& array, size_t index): array_(array), index_(index) {}
            bool operator=(bool value) {
                return array_.set(index_, value);
            }
            bool operator==(bool value) {
                return array_.set(index_, value);
            }
    };
    
    BitReference operator[](size_t index) {
        // TODO: реализуйте оператор доступа к биту
        return BitReference(*this, index);
    }
    
    // Вывод содержимого массива
    void print() const {
        // TODO: реализуйте вывод битов
        for (size_t i = 0; i < size_; i++) {
            std::cout << get(i) << " ";
        }
        std::cout << std::endl;
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
