#include <iostream>
#include <cassert>
#include <memory>
#include <vector>

// Task 6: Умные указатели для массивов
//
// Реализуйте класс ArrayManager, который:
// 1. Использует unique_ptr для массивов
// 2. Правильно работает с make_unique для массивов
// 3. Предоставляет безопасный доступ к элементам

class ArrayManager {
    std::unique_ptr<int[]> data_;
    size_t size_;
    
public:
    // TODO: Конструктор (создает массив через make_unique)
    ArrayManager(size_t size) : size_(size) {
        // TODO: создайте массив через std::make_unique<int[]>
    }
    
    // TODO: Деструктор не нужен (unique_ptr автоматически освободит память)
    
    // TODO: Получить размер
    size_t size() const {
        // TODO: реализуйте
        return 0;
    }
    
    // TODO: Доступ к элементу
    int& operator[](size_t index) {
        // TODO: реализуйте доступ к элементу массива
        static int dummy = 0;
        return dummy;
    }
    
    // TODO: Константная версия оператора []
    const int& operator[](size_t index) const {
        // TODO: реализуйте
        static const int dummy = 0;
        return dummy;
    }
    
    // TODO: Запретить копирование
    ArrayManager(const ArrayManager&) = delete;
    ArrayManager& operator=(const ArrayManager&) = delete;
    
    // TODO: Разрешить перемещение
    ArrayManager(ArrayManager&&) = default;
    ArrayManager& operator=(ArrayManager&&) = default;
};

// Код для проверки
void testArraySmartPtr() {
    ArrayManager arr(10);
    
    assert(arr.size() == 10);
    
    // Заполнение массива
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = static_cast<int>(i * 2);
    }
    
    // Проверка значений
    assert(arr[0] == 0);
    assert(arr[5] == 10);
    assert(arr[9] == 18);
    
    // Перемещение
    ArrayManager moved = std::move(arr);
    assert(moved.size() == 10);
    assert(moved[5] == 10);
    
    std::cout << "Array smart pointer tests passed!\n";
}

int main() {
    testArraySmartPtr();
    return 0;
}

