#include <iostream>
#include <cassert>
#include <memory>

// Task 1: Базовое использование std::uninitialized_fill
//
// Реализуйте функцию createFilledArray, которая:
// 1. Выделяет память для массива без инициализации
// 2. Использует std::uninitialized_fill для заполнения всех элементов значением
// 3. Правильно освобождает память после использования

// TODO: Создать массив и заполнить его значением
int* createFilledArray(size_t size, int value) {
    // TODO: выделите память через operator new[] (без инициализации)
    // TODO: используйте std::uninitialized_fill для заполнения
    // TODO: верните указатель на массив
    return nullptr;
}

// TODO: Освободить массив созданный через createFilledArray
void destroyArray(int* arr, size_t size) {
    // TODO: используйте std::destroy_n для вызова деструкторов
    // TODO: освободите память через operator delete[]
}

// Код для проверки
void testUninitializedFill() {
    const size_t size = 10;
    const int fill_value = 42;
    
    // Создание и заполнение массива
    int* arr = createFilledArray(size, fill_value);
    assert(arr != nullptr);
    
    // Проверка значений
    for (size_t i = 0; i < size; ++i) {
        assert(arr[i] == fill_value);
    }
    
    // Освобождение памяти
    destroyArray(arr, size);
    
    std::cout << "Uninitialized fill tests passed!\n";
}

int main() {
    testUninitializedFill();
    return 0;
}

