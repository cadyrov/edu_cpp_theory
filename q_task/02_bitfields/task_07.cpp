#include <iostream>
#include <cstdint>
#include <chrono>
#include <iomanip>
#include <cassert>

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
    uint16_t year_:12;
    uint8_t day_:5;
    uint8_t month_:4;
    uint8_t weekday_:3;
    
public:
    // Конструктор по умолчанию (текущая дата)
    PackedDate() {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto tm = std::localtime(&time_t);
        setDate(tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
    }
    
    // Конструктор с параметрами
    PackedDate(uint16_t year, uint8_t month, uint8_t day){
        if (!isValidDate(year, month, day)){
            throw std::invalid_argument("Invalid date");
        }

        setDate(year, month, day);
    }
    
    // Установка даты
    bool setDate(uint16_t year, uint8_t month, uint8_t day) {
        if (!isValidDate(year, month, day) ){
            return false;
        }

        year_ = year - 1970;
        month_ = month;
        day_ = day;
        weekday_ = calculateWeekday(year, month, day);
        
        return true;
    }
    
    // Получение компонентов даты
    uint16_t getYear() const {
        return 1970 + year_;
    }
    
    uint8_t getMonth() const {
        return  month_;
    }
    
    uint8_t getDay() const {
        return day_;
    }
    
    // Получение дня недели (0=воскресенье)
    uint8_t getWeekday() const {
        return weekday_;
    }
    
    // Проверка корректности даты
    static bool isValidDate(uint16_t year, uint8_t month, uint8_t day) {
        if (year < 1970 || year > 4095) {
            return false;
        }

        if (month > 12 || day > 31 || day < 1) {
            return false;
        }

        if (day > getDaysInMonth(year, month)) {
            return false;
        }

        return true;
    }
    
    // Вычисление дня недели по алгоритму Зеллера
    static uint8_t calculateWeekday(uint16_t year, uint8_t month, uint8_t day) {
        if (month == 1 || month == 2) {
            year -=1;
            month +=10;
        } else {
            month -=2;
        }
        return (day + (31 * month)/12 + year + year/4 - year/100 + year/400) %7;
    }
    
    static bool isLeapYear(uint16_t year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // Получение количества дней в месяце
    static uint8_t getDaysInMonth(uint16_t year, uint8_t month) {
        static const uint8_t days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && isLeapYear(year)) {
            return 29;
        }
        return days[month - 1];
    }

    // Вывод даты в формате YYYY-MM-DD (WWW)
   friend std::ostream& operator << (std::ostream& os, const PackedDate& date) {
    os << date.getYear() << '-'
    << std::setw(2) << std::setfill('0') << static_cast<int>(date.getMonth()) << '-'
    << std::setw(2) << std::setfill('0') << static_cast<int>(date.getDay())
    << " (" << static_cast<int>(date.getWeekday()) << ")";
 return os;
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
    std::cout << date << std::endl;
}

int main() {
    testPackedDate();
    return 0;
}
