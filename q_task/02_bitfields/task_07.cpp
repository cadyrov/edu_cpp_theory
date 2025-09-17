#include <iostream>
#include <cstdint>

// Task 7: Упакованная дата
// 
// Реализуйте структуру PackedDate, которая:
// 1. Хранит дату в компактном виде используя битовые поля:
//    - year: 12 бит (0-4095, относительно 1970)
//    - month: 4 бита (1-12)
//    - day: 5 бит (1-31)
//    - weekday: 3 бита (0-6, 0=воскресенье)
// 2. Предоставляет методы для установки и получения даты
// 3. Проверяет корректность даты
// 4. Вычисляет день недели
//
// Структура должна занимать 3 байта

class PackedDate {
    // TODO: реализуйте структуру для хранения даты
    
public:
    // Конструктор по умолчанию (текущая дата)
    PackedDate() {
        // TODO: реализуйте конструктор
    }
    
    // Конструктор с параметрами
    PackedDate(uint16_t year, uint8_t month, uint8_t day) {
        // TODO: реализуйте конструктор
    }
    
    // Установка даты
    bool setDate(uint16_t year, uint8_t month, uint8_t day) {
        // TODO: реализуйте метод установки даты с проверкой корректности
        return false;
    }
    
    // Получение компонентов даты
    uint16_t getYear() const {
        // TODO: реализуйте получение года (добавить 1970)
        return 0;
    }
    
    uint8_t getMonth() const {
        // TODO: реализуйте получение месяца
        return 0;
    }
    
    uint8_t getDay() const {
        // TODO: реализуйте получение дня
        return 0;
    }
    
    // Получение дня недели (0=воскресенье)
    uint8_t getWeekday() const {
        // TODO: реализуйте получение дня недели
        return 0;
    }
    
    // Проверка корректности даты
    static bool isValidDate(uint16_t year, uint8_t month, uint8_t day) {
        // TODO: реализуйте проверку корректности даты
        return false;
    }
    
    // Вычисление дня недели по алгоритму Зеллера
    static uint8_t calculateWeekday(uint16_t year, uint8_t month, uint8_t day) {
        // TODO: реализуйте вычисление дня недели
        return 0;
    }
    
    // Вывод даты в формате YYYY-MM-DD (WWW)
    void printDate() const {
        // TODO: реализуйте вывод даты
    }
};

// Код для проверки
void testPackedDate() {
    static_assert(sizeof(PackedDate) == 3, "PackedDate должна занимать 3 байта!");
    
    // Тест конструктора и получения значений
    PackedDate date(2023, 9, 17);
    assert(date.getYear() == 2023);
    assert(date.getMonth() == 9);
    assert(date.getDay() == 17);
    
    // Тест проверки корректности даты
    assert(PackedDate::isValidDate(2023, 9, 17) == true);
    assert(PackedDate::isValidDate(2023, 13, 1) == false);  // неверный месяц
    assert(PackedDate::isValidDate(2023, 4, 31) == false);  // неверный день
    
    // Тест установки даты
    assert(date.setDate(2024, 2, 29) == true);  // високосный год
    assert(date.setDate(2023, 2, 29) == false); // не високосный год
    
    // Тест дня недели
    PackedDate sunday(2023, 9, 17);  // это воскресенье
    assert(sunday.getWeekday() == 0);
    
    std::cout << "PackedDate tests passed!\n";
    
    // Демонстрация вывода
    date.printDate();
}

int main() {
    testPackedDate();
    return 0;
}
