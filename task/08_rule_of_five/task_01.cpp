#include <iostream>
#include <cassert>
#include <cstring>

// Task 1: Базовое использование Rule of Five
//
// Реализуйте класс Buffer, который:
// 1. Определяет все пять специальных функций
// 2. Правильно управляет динамической памятью
// 3. Предотвращает утечки и double-delete

class Buffer {
    char* data_;
    size_t size_;
    
public:
    // TODO: Конструктор
    Buffer(size_t size) : size_(size) {
        // TODO: выделите память для data_
        // TODO: инициализируйте нулями
    }
    
    // TODO: Деструктор (1 из 5)
    ~Buffer() {
        // TODO: освободите память
    }
    
    // TODO: Конструктор копирования (2 из 5)
    Buffer(const Buffer& other) : size_(other.size_) {
        // TODO: выделите новую память
        // TODO: скопируйте данные из other
    }
    
    // TODO: Оператор присваивания копированием (3 из 5)
    Buffer& operator=(const Buffer& other) {
        // TODO: проверьте самоприсваивание
        // TODO: освободите старую память
        // TODO: выделите новую память
        // TODO: скопируйте данные
        return *this;
    }
    
    // TODO: Конструктор перемещения (4 из 5)
    Buffer(Buffer&& other) noexcept {
        // TODO: переместите данные из other
        // TODO: обнулите other
    }
    
    // TODO: Оператор присваивания перемещением (5 из 5)
    Buffer& operator=(Buffer&& other) noexcept {
        // TODO: проверьте самоприсваивание
        // TODO: освободите старую память
        // TODO: переместите данные из other
        // TODO: обнулите other
        return *this;
    }
    
    size_t getSize() const { return size_; }
    const char* getData() const { return data_; }
    char* getData() { return data_; }
};

// Код для проверки
void testRuleOfFive() {
    // Создание
    Buffer buf1(100);
    assert(buf1.getSize() == 100);
    
    // Копирование
    Buffer buf2 = buf1;
    assert(buf2.getSize() == 100);
    assert(buf2.getData() != buf1.getData());  // Разная память
    
    // Присваивание копированием
    Buffer buf3(50);
    buf3 = buf1;
    assert(buf3.getSize() == 100);
    
    // Перемещение
    Buffer buf4 = std::move(buf1);
    assert(buf4.getSize() == 100);
    assert(buf1.getSize() == 0);  // buf1 должен быть пустым
    
    // Присваивание перемещением
    Buffer buf5(200);
    buf5 = std::move(buf4);
    assert(buf5.getSize() == 100);
    assert(buf4.getSize() == 0);
    
    // Самоприсваивание
    buf5 = buf5;
    assert(buf5.getSize() == 100);
    
    std::cout << "Rule of Five basic tests passed!\n";
}

int main() {
    testRuleOfFive();
    return 0;
}

