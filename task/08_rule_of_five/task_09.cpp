#include <iostream>
#include <cassert>
#include <vector>
#include <utility>

// Task 9: noexcept для move операций
//
// Реализуйте класс NoThrowMovable, который:
// 1. Имеет move операции помеченные как noexcept
// 2. Использует noexcept для оптимизации
// 3. Правильно обрабатывает исключения

class NoThrowMovable {
    std::vector<int>* data_;
    size_t size_;
    
public:
    // Конструктор
    NoThrowMovable(size_t size) : size_(size) {
        data_ = new std::vector<int>(size);
    }
    
    // Конструктор копирования
    NoThrowMovable(const NoThrowMovable& other) : size_(other.size_) {
        data_ = new std::vector<int>(*other.data_);
    }
    
    // TODO: Конструктор перемещения (noexcept)
    NoThrowMovable(NoThrowMovable&& other) noexcept {
        // TODO: переместите data_ и size_
        // TODO: обнулите other
        // TODO: обязательно пометьте как noexcept
    }
    
    // Оператор присваивания копированием
    NoThrowMovable& operator=(const NoThrowMovable& other) {
        if (this != &other) {
            delete data_;
            size_ = other.size_;
            data_ = new std::vector<int>(*other.data_);
        }
        return *this;
    }
    
    // TODO: Оператор присваивания перемещением (noexcept)
    NoThrowMovable& operator=(NoThrowMovable&& other) noexcept {
        // TODO: проверьте самоприсваивание
        // TODO: освободите старую память
        // TODO: переместите данные из other
        // TODO: обнулите other
        // TODO: обязательно пометьте как noexcept
        return *this;
    }
    
    // Деструктор
    ~NoThrowMovable() {
        delete data_;
    }
    
    void setValue(size_t index, int value) {
        if (data_ && index < data_->size()) {
            (*data_)[index] = value;
        }
    }
    
    int getValue(size_t index) const {
        return (data_ && index < data_->size()) ? (*data_)[0] : 0;
    }
    
    size_t getSize() const { return size_; }
    bool isEmpty() const { return data_ == nullptr; }
};

// Код для проверки
void testNoexceptMove() {
    // Создание
    NoThrowMovable obj1(10);
    obj1.setValue(0, 42);
    
    // Проверка что move конструктор noexcept
    static_assert(noexcept(NoThrowMovable(std::declval<NoThrowMovable&&>())),
                  "Move constructor should be noexcept");
    
    // Проверка что move assignment noexcept
    static_assert(noexcept(std::declval<NoThrowMovable&>() = std::declval<NoThrowMovable&&>()),
                  "Move assignment should be noexcept");
    
    // Перемещение
    NoThrowMovable obj2 = std::move(obj1);
    assert(obj2.getSize() == 10);
    assert(obj1.isEmpty());
    
    // Перемещающее присваивание
    NoThrowMovable obj3(5);
    obj3 = std::move(obj2);
    assert(obj3.getSize() == 10);
    assert(obj2.isEmpty());
    
    // Перемещение из временного объекта
    NoThrowMovable obj4 = NoThrowMovable(20);
    assert(obj4.getSize() == 20);
    
    std::cout << "Noexcept move operations tests passed!\n";
}

int main() {
    testNoexceptMove();
    return 0;
}

