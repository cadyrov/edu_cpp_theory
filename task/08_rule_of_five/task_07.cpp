#include <iostream>
#include <cassert>
#include <algorithm>
#include <utility>

// Task 7: Copy-and-swap идиома
//
// Реализуйте класс SwappableArray используя copy-and-swap:
// 1. Реализуйте метод swap
// 2. Используйте copy-and-swap в операторе присваивания
// 3. Обеспечьте строгую гарантию exception safety

class SwappableArray {
    int* data_;
    size_t size_;
    
public:
    // Конструктор
    SwappableArray(size_t size) : size_(size) {
        data_ = new int[size_];
        std::fill(data_, data_ + size_, 0);
    }
    
    // Конструктор копирования
    SwappableArray(const SwappableArray& other) : size_(other.size_) {
        data_ = new int[size_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
    
    // Конструктор перемещения
    SwappableArray(SwappableArray&& other) noexcept
        : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
    }
    
    // Деструктор
    ~SwappableArray() {
        delete[] data_;
    }
    
    // TODO: Метод swap (noexcept)
    void swap(SwappableArray& other) noexcept {
        // TODO: используйте std::swap для обмена data_ и size_
    }
    
    // TODO: Оператор присваивания через copy-and-swap
    SwappableArray& operator=(const SwappableArray& other) {
        // TODO: создайте временную копию other
        // TODO: используйте swap для атомарной замены
        // TODO: это обеспечивает строгую гарантию exception safety
        return *this;
    }
    
    // Оператор присваивания перемещением через swap
    SwappableArray& operator=(SwappableArray&& other) noexcept {
        swap(other);
        return *this;
    }
    
    void setValue(size_t index, int value) {
        if (index < size_) {
            data_[index] = value;
        }
    }
    
    int getValue(size_t index) const {
        return (index < size_) ? data_[index] : 0;
    }
    
    size_t getSize() const { return size_; }
    int* getData() const { return data_; }
};

// Код для проверки
void testCopyAndSwap() {
    // Создание массивов
    SwappableArray arr1(5);
    arr1.setValue(0, 10);
    arr1.setValue(1, 20);
    
    SwappableArray arr2(3);
    arr2.setValue(0, 100);
    
    // Присваивание через copy-and-swap
    arr2 = arr1;
    assert(arr2.getSize() == 5);
    assert(arr2.getValue(0) == 10);
    assert(arr2.getValue(1) == 20);
    
    // Проверка что это разные объекты
    arr2.setValue(0, 999);
    assert(arr1.getValue(0) == 10);  // arr1 не изменился
    
    // Тест swap
    SwappableArray arr3(2);
    arr3.setValue(0, 50);
    int* arr3_ptr = arr3.getData();
    size_t arr3_size = arr3.getSize();
    
    arr1.swap(arr3);
    assert(arr1.getSize() == 2);
    assert(arr1.getData() == arr3_ptr);
    assert(arr3.getSize() == 5);
    
    // Проверка что swap noexcept
    static_assert(noexcept(std::declval<SwappableArray>().swap(std::declval<SwappableArray&>())),
                  "swap should be noexcept");
    
    // Самоприсваивание
    SwappableArray arr4(4);
    arr4.setValue(0, 42);
    arr4 = arr4;
    assert(arr4.getSize() == 4);
    assert(arr4.getValue(0) == 42);
    
    std::cout << "Copy-and-swap tests passed!\n";
}

int main() {
    testCopyAndSwap();
    return 0;
}

