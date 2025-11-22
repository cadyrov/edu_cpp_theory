#include <iostream>
#include <cassert>
#include <cstring>

// Task 3: Оператор присваивания копированием
//
// Реализуйте класс StringBuffer с правильным оператором присваивания:
// 1. Обработка самоприсваивания
// 2. Освобождение старой памяти
// 3. Копирование новых данных

class StringBuffer {
    char* data_;
    size_t length_;
    
public:
    // Конструктор
    StringBuffer(const char* str = "") {
        length_ = strlen(str);
        data_ = new char[length_ + 1];
        strcpy(data_, str);
    }
    
    // Конструктор копирования
    StringBuffer(const StringBuffer& other) 
        : length_(other.length_) {
        data_ = new char[length_ + 1];
        strcpy(data_, other.data_);
    }
    
    // TODO: Оператор присваивания копированием
    StringBuffer& operator=(const StringBuffer& other) {
        // TODO: проверьте самоприсваивание
        // TODO: освободите старую память
        // TODO: скопируйте length_
        // TODO: выделите новую память
        // TODO: скопируйте данные
        return *this;
    }
    
    // Деструктор
    ~StringBuffer() {
        delete[] data_;
    }
    
    // Запретить перемещение для этого задания
    StringBuffer(StringBuffer&&) = delete;
    StringBuffer& operator=(StringBuffer&&) = delete;
    
    const char* getData() const { return data_; }
    size_t getLength() const { return length_; }
};

// Код для проверки
void testCopyAssignment() {
    // Создание объектов
    StringBuffer buf1("Hello");
    StringBuffer buf2("World");
    
    assert(strcmp(buf1.getData(), "Hello") == 0);
    assert(strcmp(buf2.getData(), "World") == 0);
    
    // Присваивание
    buf2 = buf1;
    assert(strcmp(buf2.getData(), "Hello") == 0);
    assert(buf2.getLength() == buf1.getLength());
    
    // Проверка что это разные объекты
    StringBuffer buf3("Test");
    buf3 = buf1;
    assert(strcmp(buf3.getData(), "Hello") == 0);
    
    // Самоприсваивание
    const char* old_data = buf1.getData();
    buf1 = buf1;
    assert(strcmp(buf1.getData(), "Hello") == 0);
    assert(buf1.getData() == old_data);  // Должен остаться тот же указатель
    
    // Присваивание более длинной строки
    StringBuffer buf4("Short");
    StringBuffer buf4_source("Very long string");
    buf4 = buf4_source;
    assert(strcmp(buf4.getData(), "Very long string") == 0);
    
    // Присваивание более короткой строки
    StringBuffer buf5("Very long string");
    StringBuffer buf5_source("Hi");
    buf5 = buf5_source;
    assert(strcmp(buf5.getData(), "Hi") == 0);
    
    std::cout << "Copy assignment operator tests passed!\n";
}

int main() {
    testCopyAssignment();
    return 0;
}

