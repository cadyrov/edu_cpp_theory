#include <iostream>
#include <cassert>
#include <memory>
#include <vector>

// Task 2: std::uninitialized_copy
//
// Реализуйте функцию copyToUninitialized, которая:
// 1. Копирует элементы из инициализированного массива в неинициализированную память
// 2. Использует std::uninitialized_copy
// 3. Правильно обрабатывает исключения

// TODO: Скопировать элементы из source в неинициализированную память
int* copyToUninitialized(const int* source, size_t count) {
    // TODO: выделите память через operator new[] (без инициализации)
    // TODO: используйте std::uninitialized_copy для копирования
    // TODO: верните указатель на новый массив
    return nullptr;
}

// TODO: Освободить скопированный массив
void destroyCopiedArray(int* arr, size_t count) {
    // TODO: используйте std::destroy_n
    // TODO: освободите память через operator delete[]
}

// Код для проверки
void testUninitializedCopy() {
    std::vector<int> source = {1, 2, 3, 4, 5};
    
    // Копирование в неинициализированную память
    int* copied = copyToUninitialized(source.data(), source.size());
    assert(copied != nullptr);
    
    // Проверка корректности копирования
    for (size_t i = 0; i < source.size(); ++i) {
        assert(copied[i] == source[i]);
    }
    
    // Освобождение памяти
    destroyCopiedArray(copied, source.size());
    
    std::cout << "Uninitialized copy tests passed!\n";
}

int main() {
    testUninitializedCopy();
    return 0;
}

