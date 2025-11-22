#include <iostream>
#include <cassert>
#include <memory>
#include <algorithm>

// Task 9: Оптимизированный вектор с reserve
//
// Реализуйте класс OptimizedVector, который:
// 1. Использует неинициализированную память для оптимизации
// 2. Правильно реализует reserve() без двойной инициализации
// 3. Использует std::uninitialized_move при реаллокации
// 4. Гарантирует exception safety

template<typename T>
class OptimizedVector {
    T* data_;
    size_t size_;
    size_t capacity_;
    
public:
    OptimizedVector() : data_(nullptr), size_(0), capacity_(0) {}
    
    // TODO: Деструктор
    ~OptimizedVector() {
        // TODO: уничтожьте элементы через std::destroy_n
        // TODO: освободите память через operator delete[]
    }
    
    // TODO: Резервировать память без инициализации
    void reserve(size_t new_capacity) {
        // TODO: если new_capacity <= capacity_, ничего не делайте
        // TODO: выделите новую память через operator new[]
        // TODO: переместите существующие элементы через std::uninitialized_move_n
        // TODO: уничтожьте старые элементы через std::destroy_n
        // TODO: освободите старую память
        // TODO: обновите data_ и capacity_
        // TODO: обработайте исключения (strong guarantee)
    }
    
    // TODO: Добавить элемент в конец
    void pushBack(const T& value) {
        // TODO: если нужно, вызовите reserve
        // TODO: используйте placement new для создания элемента
        // TODO: обновите size_
    }
    
    // TODO: Получить размер
    size_t size() const { return size_; }
    
    // TODO: Получить емкость
    size_t capacity() const { return capacity_; }
    
    // TODO: Оператор доступа
    const T& operator[](size_t index) const {
        return data_[index];
    }
    
    T& operator[](size_t index) {
        return data_[index];
    }
};

// Код для проверки
void testOptimizedVector() {
    OptimizedVector<int> vec;
    
    // Резервирование памяти
    vec.reserve(10);
    assert(vec.capacity() == 10);
    assert(vec.size() == 0);
    
    // Добавление элементов
    for (int i = 0; i < 5; ++i) {
        vec.pushBack(i * 10);
    }
    
    assert(vec.size() == 5);
    assert(vec.capacity() == 10);
    
    // Проверка значений
    for (size_t i = 0; i < vec.size(); ++i) {
        assert(vec[i] == static_cast<int>(i * 10));
    }
    
    // Расширение capacity
    vec.reserve(20);
    assert(vec.capacity() == 20);
    assert(vec.size() == 5);
    
    // Проверка что элементы сохранились после реаллокации
    for (size_t i = 0; i < vec.size(); ++i) {
        assert(vec[i] == static_cast<int>(i * 10));
    }
    
    std::cout << "OptimizedVector tests passed!\n";
}

int main() {
    testOptimizedVector();
    return 0;
}

