#include <iostream>

// Task 6: Константные указатели
// 
// Задача на понимание:
// 1. Разницы между const pointer и pointer to const
// 2. East const vs West const стилей
// 3. Комбинации const pointer to const data
// 4. Правильного использования константных указателей

class Settings {
    int value_;
public:
    Settings(int v) : value_(v) {}
    void setValue(int v) { value_ = v; }
    int getValue() const { return value_; }
};

// TODO: Реализуйте функции, которые демонстрируют различные случаи использования константных указателей:

// 1. Функция, принимающая указатель на константные данные (нельзя менять *ptr)
void printSettings(/* TODO */);

// 2. Функция, принимающая константный указатель (нельзя менять ptr)
void rememberSettings(/* TODO */);

// 3. Функция, принимающая константный указатель на константные данные (нельзя менять ни ptr, ни *ptr)
void archiveSettings(/* TODO */);

// Код для проверки
void testConstPointers() {
    Settings s1(42), s2(123);
    Settings* ptr1 = &s1;
    const Settings* ptr2 = &s2;
    Settings* const ptr3 = &s1;
    const Settings* const ptr4 = &s2;
    
    // Эти строки должны компилироваться:
    printSettings(ptr1);     // Можно передать обычный указатель
    printSettings(ptr2);     // Можно передать указатель на const
    rememberSettings(ptr1);  // Можно передать обычный указатель
    archiveSettings(ptr2);   // Можно передать указатель на const
    
    // Эти строки НЕ должны компилироваться:
    // ptr2->setValue(456);    // Нельзя менять данные через указатель на const
    // ptr3 = &s2;            // Нельзя менять сам константный указатель
    // ptr4->setValue(789);   // Нельзя менять данные через константный указатель на const
    // ptr4 = &s1;            // Нельзя менять сам константный указатель на const
}
