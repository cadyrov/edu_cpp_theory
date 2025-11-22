#include <iostream>
#include <cassert>
#include <cstring>

// Task 5: Оператор присваивания перемещением
//
// Реализуйте класс DynamicString с оператором присваивания перемещением:
// 1. Освобождение старого ресурса
// 2. Перемещение нового ресурса
// 3. Обнуление исходного объекта
// 4. Обработка самоприсваивания

class DynamicString {
    char* data_;
    size_t capacity_;
    
public:
    // Конструктор
    DynamicString(size_t capacity) : capacity_(capacity) {
        data_ = new char[capacity_];
        data_[0] = '\0';
    }
    
    // Конструктор копирования
    DynamicString(const DynamicString& other) 
        : capacity_(other.capacity_) {
        data_ = new char[capacity_];
        strcpy(data_, other.data_);
    }
    
    // Конструктор перемещения
    DynamicString(DynamicString&& other) noexcept
        : data_(other.data_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
    }
    
    // Оператор присваивания копированием
    DynamicString& operator=(const DynamicString& other) {
        if (this != &other) {
            delete[] data_;
            capacity_ = other.capacity_;
            data_ = new char[capacity_];
            strcpy(data_, other.data_);
        }
        return *this;
    }
    
    // TODO: Оператор присваивания перемещением (noexcept)
    DynamicString& operator=(DynamicString&& other) noexcept {
        // TODO: проверьте самоприсваивание
        // TODO: освободите старую память
        // TODO: переместите data_ из other
        // TODO: переместите capacity_
        // TODO: обнулите other
        return *this;
    }
    
    // Деструктор
    ~DynamicString() {
        delete[] data_;
    }
    
    void setString(const char* str) {
        if (data_ && strlen(str) < capacity_) {
            strcpy(data_, str);
        }
    }
    
    const char* getString() const { return data_ ? data_ : ""; }
    size_t getCapacity() const { return capacity_; }
    bool isEmpty() const { return data_ == nullptr; }
};

// Код для проверки
void testMoveAssignment() {
    // Создание объектов
    DynamicString str1(100);
    str1.setString("Hello");
    DynamicString str2(50);
    str2.setString("World");
    
    const char* str1_data = str1.getString();
    
    // Перемещающее присваивание
    str2 = std::move(str1);
    
    // Проверка что данные перемещены
    assert(strcmp(str2.getString(), "Hello") == 0);
    assert(str1.isEmpty());  // str1 должен быть пустым
    
    // Проверка перемещения
    DynamicString str3(200);
    str3.setString("Test");
    DynamicString str4(300);
    str4 = std::move(str3);
    assert(strcmp(str4.getString(), "Test") == 0);
    assert(str3.isEmpty());
    
    // Самоприсваивание перемещением
    DynamicString str5(100);
    str5.setString("Self");
    str5 = std::move(str5);
    assert(strcmp(str5.getString(), "Self") == 0);
    
    // Проверка что оператор noexcept
    static_assert(noexcept(std::declval<DynamicString&>() = std::declval<DynamicString&&>()),
                  "Move assignment should be noexcept");
    
    std::cout << "Move assignment operator tests passed!\n";
}

int main() {
    testMoveAssignment();
    return 0;
}

