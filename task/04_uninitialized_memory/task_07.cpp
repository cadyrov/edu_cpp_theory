#include <iostream>
#include <cassert>
#include <memory>
#include <string>

// Task 7: std::destroy для освобождения
//
// Реализуйте класс DynamicArray, который:
// 1. Управляет массивом объектов с неинициализированной памятью
// 2. Правильно вызывает деструкторы через std::destroy_n
// 3. Поддерживает добавление и удаление элементов

class DynamicArray {
    std::string* data_;
    size_t size_;
    size_t capacity_;
    
public:
    DynamicArray() : data_(nullptr), size_(0), capacity_(0) {}
    
    // TODO: Резервировать память без инициализации
    void reserve(size_t new_capacity) {
        // TODO: выделите память через operator new[]
        // TODO: обновите capacity_
    }
    
    // TODO: Добавить элемент в конец
    void pushBack(const std::string& value) {
        // TODO: если нужно, увеличьте capacity
        // TODO: используйте placement new для создания элемента
        // TODO: обновите size_
    }
    
    // TODO: Удалить последний элемент
    void popBack() {
        // TODO: используйте std::destroy_at для вызова деструктора
        // TODO: обновите size_
    }
    
    // TODO: Очистить массив
    void clear() {
        // TODO: используйте std::destroy_n для всех элементов
        // TODO: обновите size_
    }
    
    // TODO: Деструктор
    ~DynamicArray() {
        // TODO: очистите массив
        // TODO: освободите память через operator delete[]
    }
    
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    
    const std::string& operator[](size_t index) const {
        return data_[index];
    }
};

// Код для проверки
void testDestroy() {
    DynamicArray arr;
    
    // Резервирование памяти
    arr.reserve(10);
    assert(arr.capacity() == 10);
    assert(arr.size() == 0);
    
    // Добавление элементов
    arr.pushBack("first");
    arr.pushBack("second");
    arr.pushBack("third");
    assert(arr.size() == 3);
    assert(arr[0] == "first");
    assert(arr[1] == "second");
    assert(arr[2] == "third");
    
    // Удаление элемента
    arr.popBack();
    assert(arr.size() == 2);
    assert(arr[0] == "first");
    assert(arr[1] == "second");
    
    // Очистка
    arr.clear();
    assert(arr.size() == 0);
    
    std::cout << "Destroy tests passed!\n";
}

int main() {
    testDestroy();
    return 0;
}

