#include <string>
#include <iostream>

// Task 5: const_cast и legacy API
// 
// У вас есть legacy C API, который не использует const.
// Нужно написать современный C++ wrapper, который:
// 1. Обеспечивает const-correctness
// 2. Безопасно работает с legacy функциями
// 3. Защищает от неправильного использования const_cast

// Legacy C API (не меняйте этот код)
extern "C" {
    struct Data {
        char* buffer;
        int length;
    };
    
    // Legacy функция, которая на самом деле не модифицирует данные
    void legacy_print(Data* data) {
        std::cout << "Buffer: " << data->buffer << "\n";
        std::cout << "Length: " << data->length << "\n";
    }
    
    // Legacy функция, которая модифицирует данные
    void legacy_modify(Data* data, const char* new_text) {
        strcpy(data->buffer, new_text);
        data->length = strlen(new_text);
    }
}

// Ваш современный C++ wrapper
class SafeData {
    Data data_;
public:
    SafeData(const char* text) {
        data_.buffer = new char[100];  // Упрощенно, в реальном коде нужен более умный менеджмент памяти
        legacy_modify(&data_, text);
    }
    
    ~SafeData() {
        delete[] data_.buffer;
    }
    
    // TODO: Реализуйте:
    // 1. Метод print() который можно вызвать для константных объектов
    // 2. Метод modify() который нельзя вызвать для константных объектов
    // 3. Метод get_length() который можно вызвать для константных объектов
    // 4. Корректную работу с legacy API, используя const_cast только где действительно необходимо
};

// Код для проверки
void testSafeData() {
    SafeData data("test");
    const SafeData const_data("const test");
    
    // Эти строки должны компилироваться:
    data.print();                  // Печать неконстантного объекта
    const_data.print();           // Печать константного объекта
    data.modify("new text");      // Модификация неконстантного объекта
    std::cout << data.get_length() << "\n";        // Длина неконстантного объекта
    std::cout << const_data.get_length() << "\n";  // Длина константного объекта
    
    // Эти строки НЕ должны компилироваться:
    // const_data.modify("new text");  // Ошибка: нельзя модифицировать константный объект
}
