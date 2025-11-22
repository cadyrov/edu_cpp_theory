#include <iostream>
#include <cassert>
#include <algorithm>

// Task 2: Конструктор копирования
//
// Реализуйте класс IntArray с правильным конструктором копирования:
// 1. Глубокое копирование данных
// 2. Правильная инициализация всех членов
// 3. Обработка граничных случаев

class IntArray {
    int* data_;
    size_t size_;
    
public:
    // Конструктор
    IntArray(size_t size) : size_(size) {
        data_ = new int[size];
        std::fill(data_, data_ + size_, 0);
    }
    
    // TODO: Конструктор копирования
    IntArray(const IntArray& other) {
        // TODO: скопируйте size_
        // TODO: выделите новую память
        // TODO: скопируйте все элементы из other
    }
    
    // Деструктор
    ~IntArray() {
        delete[] data_;
    }
    
    // Запретить присваивание и перемещение для этого задания
    IntArray& operator=(const IntArray&) = delete;
    IntArray(IntArray&&) = delete;
    IntArray& operator=(IntArray&&) = delete;
    
    // Методы доступа
    void setValue(size_t index, int value) {
        if (index < size_) {
            data_[index] = value;
        }
    }
    
    int getValue(size_t index) const {
        return (index < size_) ? data_[index] : 0;
    }
    
    size_t getSize() const { return size_; }
    
    // Метод для проверки что это разные объекты
    int* getDataPtr() const { return data_; }
};

// Код для проверки
void testCopyConstructor() {
    // Создание исходного массива
    IntArray arr1(5);
    arr1.setValue(0, 10);
    arr1.setValue(1, 20);
    arr1.setValue(2, 30);
    
    // Копирование
    IntArray arr2 = arr1;
    
    // Проверка что данные скопированы
    assert(arr2.getSize() == 5);
    assert(arr2.getValue(0) == 10);
    assert(arr2.getValue(1) == 20);
    assert(arr2.getValue(2) == 30);
    
    // Проверка что это разные объекты (разная память)
    assert(arr2.getDataPtr() != arr1.getDataPtr());
    
    // Изменение одного не должно влиять на другой
    arr2.setValue(0, 100);
    assert(arr1.getValue(0) == 10);  // arr1 не изменился
    assert(arr2.getValue(0) == 100);  // arr2 изменился
    
    // Копирование пустого массива
    IntArray arr3(0);
    IntArray arr4 = arr3;
    assert(arr4.getSize() == 0);
    
    std::cout << "Copy constructor tests passed!\n";
}

int main() {
    testCopyConstructor();
    return 0;
}

