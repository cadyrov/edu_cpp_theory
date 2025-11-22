#include <iostream>
#include <cassert>
#include <cstring>

// Task 4: Работа с POD типами
//
// Реализуйте функции для работы с POD типами:
// 1. Копирование POD структур через memcpy
// 2. Создание массива POD структур без инициализации
// 3. Безопасное копирование POD данных

struct POD {
    int x;
    double y;
    char z;
};

// TODO: Скопировать POD структуру в неинициализированную память
void copyPOD(const POD& source, POD* dest) {
    // TODO: используйте std::memcpy для копирования POD структуры
}

// TODO: Создать массив POD структур и заполнить их значениями
POD* createPODArray(size_t count, const POD& value) {
    // TODO: выделите память через operator new[]
    // TODO: используйте std::uninitialized_fill_n для заполнения
    return nullptr;
}

// TODO: Освободить массив POD структур
void destroyPODArray(POD* arr, size_t count) {
    // TODO: освободите память через operator delete[]
    // Подсказка: для POD типов деструкторы тривиальные, но лучше использовать std::destroy_n
}

// Код для проверки
void testPODTypes() {
    POD source{42, 3.14, 'A'};
    
    // Копирование одной структуры
    POD* single = static_cast<POD*>(::operator new(sizeof(POD)));
    copyPOD(source, single);
    assert(single->x == 42);
    assert(single->y == 3.14);
    assert(single->z == 'A');
    ::operator delete(single);
    
    // Создание массива
    POD* arr = createPODArray(5, source);
    assert(arr != nullptr);
    
    // Проверка значений
    for (size_t i = 0; i < 5; ++i) {
        assert(arr[i].x == 42);
        assert(arr[i].y == 3.14);
        assert(arr[i].z == 'A');
    }
    
    destroyPODArray(arr, 5);
    
    std::cout << "POD types tests passed!\n";
}

int main() {
    testPODTypes();
    return 0;
}

