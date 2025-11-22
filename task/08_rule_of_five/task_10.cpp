#include <iostream>
#include <cassert>
#include <cstring>
#include <utility>

// Task 10: Комбинированная задача - полная реализация Rule of Five
//
// Реализуйте класс CompleteBuffer, который:
// 1. Определяет все пять специальных функций
// 2. Использует copy-and-swap для присваивания
// 3. Правильно помечает move операции как noexcept
// 4. Обеспечивает exception safety

class CompleteBuffer {
    char* data_;
    size_t size_;
    size_t capacity_;
    
public:
    // TODO: Конструктор
    CompleteBuffer(size_t capacity) : capacity_(capacity), size_(0) {
        // TODO: выделите память для data_
        // TODO: инициализируйте data_[0] = '\0'
    }
    
    // TODO: Деструктор
    ~CompleteBuffer() {
        // TODO: освободите память
    }
    
    // TODO: Конструктор копирования
    CompleteBuffer(const CompleteBuffer& other) 
        : capacity_(other.capacity_), size_(other.size_) {
        // TODO: выделите память
        // TODO: скопируйте данные
    }
    
    // TODO: Конструктор перемещения (noexcept)
    CompleteBuffer(CompleteBuffer&& other) noexcept {
        // TODO: переместите все данные из other
        // TODO: обнулите other
    }
    
    // TODO: Метод swap (noexcept)
    void swap(CompleteBuffer& other) noexcept {
        // TODO: обменяйте все члены используя std::swap
    }
    
    // TODO: Оператор присваивания копированием (через copy-and-swap)
    CompleteBuffer& operator=(const CompleteBuffer& other) {
        // TODO: создайте временную копию
        // TODO: используйте swap
        return *this;
    }
    
    // TODO: Оператор присваивания перемещением (noexcept, через swap)
    CompleteBuffer& operator=(CompleteBuffer&& other) noexcept {
        // TODO: используйте swap
        return *this;
    }
    
    // Методы для работы с буфером
    void append(const char* str) {
        size_t len = strlen(str);
        if (size_ + len < capacity_) {
            strcpy(data_ + size_, str);
            size_ += len;
        }
    }
    
    const char* getData() const { return data_ ? data_ : ""; }
    size_t getSize() const { return size_; }
    size_t getCapacity() const { return capacity_; }
    bool isEmpty() const { return data_ == nullptr; }
};

// Код для проверки
void testCompleteRuleOfFive() {
    // Создание
    CompleteBuffer buf1(100);
    buf1.append("Hello");
    assert(strcmp(buf1.getData(), "Hello") == 0);
    assert(buf1.getSize() == 5);
    
    // Копирование
    CompleteBuffer buf2 = buf1;
    assert(strcmp(buf2.getData(), "Hello") == 0);
    assert(buf2.getSize() == 5);
    assert(buf2.getData() != buf1.getData());  // Разная память
    
    // Присваивание копированием
    CompleteBuffer buf3(50);
    buf3 = buf1;
    assert(strcmp(buf3.getData(), "Hello") == 0);
    
    // Перемещение
    CompleteBuffer buf4 = std::move(buf1);
    assert(strcmp(buf4.getData(), "Hello") == 0);
    assert(buf4.getSize() == 5);
    assert(buf1.isEmpty());
    
    // Перемещающее присваивание
    CompleteBuffer buf5(200);
    buf5 = std::move(buf4);
    assert(strcmp(buf5.getData(), "Hello") == 0);
    assert(buf4.isEmpty());
    
    // Самоприсваивание
    buf5 = buf5;
    assert(strcmp(buf5.getData(), "Hello") == 0);
    
    // Тест swap
    CompleteBuffer buf6(150);
    buf6.append("World");
    buf5.swap(buf6);
    assert(strcmp(buf5.getData(), "World") == 0);
    assert(strcmp(buf6.getData(), "Hello") == 0);
    
    // Проверка noexcept
    static_assert(noexcept(CompleteBuffer(std::declval<CompleteBuffer&&>())),
                  "Move constructor should be noexcept");
    static_assert(noexcept(std::declval<CompleteBuffer&>() = std::declval<CompleteBuffer&&>()),
                  "Move assignment should be noexcept");
    static_assert(noexcept(std::declval<CompleteBuffer>().swap(std::declval<CompleteBuffer&>())),
                  "swap should be noexcept");
    
    std::cout << "Complete Rule of Five tests passed!\n";
}

int main() {
    testCompleteRuleOfFive();
    return 0;
}

