#include <iostream>
#include <cassert>
#include <memory>
#include <vector>

// Task 6: std::uninitialized_move
//
// Реализуйте функцию moveToUninitialized, которая:
// 1. Перемещает элементы из одного массива в неинициализированную память
// 2. Использует std::uninitialized_move
// 3. Правильно обрабатывает перемещение

class MovableObject {
    int* data_;
public:
    MovableObject(int value) : data_(new int(value)) {}
    
    // Конструктор перемещения
    MovableObject(MovableObject&& other) noexcept 
        : data_(other.data_) {
        other.data_ = nullptr;
    }
    
    // Оператор перемещения
    MovableObject& operator=(MovableObject&& other) noexcept {
        if (this != &other) {
            delete data_;
            data_ = other.data_;
            other.data_ = nullptr;
        }
        return *this;
    }
    
    // Запрет копирования
    MovableObject(const MovableObject&) = delete;
    MovableObject& operator=(const MovableObject&) = delete;
    
    ~MovableObject() { delete data_; }
    
    int getValue() const { return data_ ? *data_ : -1; }
};

// TODO: Переместить элементы в неинициализированную память
MovableObject* moveToUninitialized(MovableObject* source, size_t count) {
    // TODO: выделите память через operator new[]
    // TODO: используйте std::uninitialized_move для перемещения
    return nullptr;
}

// TODO: Освободить перемещенный массив
void destroyMovedArray(MovableObject* arr, size_t count) {
    // TODO: используйте std::destroy_n
    // TODO: освободите память через operator delete[]
}

// Код для проверки
void testUninitializedMove() {
    // Создание исходного массива
    std::vector<MovableObject> source;
    source.emplace_back(10);
    source.emplace_back(20);
    source.emplace_back(30);
    
    // Перемещение в неинициализированную память
    MovableObject* moved = moveToUninitialized(source.data(), source.size());
    assert(moved != nullptr);
    
    // Проверка перемещенных значений
    assert(moved[0].getValue() == 10);
    assert(moved[1].getValue() == 20);
    assert(moved[2].getValue() == 30);
    
    // Исходные объекты должны быть в валидном состоянии после перемещения
    // (но их значения могут быть неопределенными)
    
    destroyMovedArray(moved, source.size());
    
    std::cout << "Uninitialized move tests passed!\n";
}

int main() {
    testUninitializedMove();
    return 0;
}

