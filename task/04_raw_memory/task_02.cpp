#include <iostream>
#include <cassert>

// Task 2: Массивы new[]/delete[]
//
// Реализуйте класс IntArray, который:
// 1. Хранит динамический массив int, выделенный через new[]
// 2. Правильно освобождает память через delete[]
// 3. Предоставляет методы для доступа к элементам
// 4. Имеет метод для получения размера массива

class IntArray {
    int* data_;
    size_t size_;
public:
    // TODO: Конструктор с размером массива
    IntArray(size_t size) {
        // TODO: реализуйте выделение памяти через new[]
    }
    
    // TODO: Деструктор (освобождает память через delete[])
    ~IntArray() {
        // TODO: реализуйте
    }
    
    // TODO: Метод для получения размера
    size_t size() const {
        // TODO: реализуйте
        return 0;
    }
    
    // TODO: Метод для доступа к элементу по индексу
    int& operator[](size_t index) {
        // TODO: реализуйте
        static int dummy = 0;
        return dummy;
    }
    
    // TODO: Константная версия оператора []
    const int& operator[](size_t index) const {
        // TODO: реализуйте
        static const int dummy = 0;
        return dummy;
    }
};

// Код для проверки
void testIntArray() {
    IntArray arr(10);
    
    // Проверка размера
    assert(arr.size() == 10);
    
    // Заполнение массива
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = static_cast<int>(i * 2);
    }
    
    // Проверка значений
    assert(arr[0] == 0);
    assert(arr[5] == 10);
    assert(arr[9] == 18);
    
    // Проверка константного доступа
    const IntArray& const_arr = arr;
    assert(const_arr[0] == 0);
    
    std::cout << "IntArray tests passed!\n";
}

int main() {
    testIntArray();
    return 0;
}

