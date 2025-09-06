# Константность (const)

## Определение
Спецификатор `const` в C++ обозначает, что значение объекта не может быть изменено после инициализации.

## Зачем это нужно
- Защита от случайных изменений данных
- Явное обозначение намерений в коде
- Возможность оптимизации для компилятора
- Поддержка thread-safety

## Примеры

### ✅ Хорошо
```cpp
// Константные параметры функции
void processUser(const User& user) {
    std::cout << user.name;  // Только чтение
}

// Константные методы класса
class BankAccount {
public:
    double getBalance() const {
        return balance;  // Гарантированно не изменяет состояние
    }
private:
    double balance;
};

// Константные указатели на константные данные
const char* const VERSION = "1.0.0";

// Использование mutable для кэша
class WebService {
    mutable std::map<std::string, Response> cache_;
public:
    Response getData(const std::string& url) const {
        if (auto it = cache_.find(url); it != cache_.end()) {
            return it->second;
        }
        Response response = fetchFromNetwork(url);
        cache_[url] = response;  // Можно модифицировать благодаря mutable
        return response;
    }
};
```

### ❌ Плохо
```cpp
// Неконстантный параметр, когда не планируем менять
void processUser(User& user) {
    std::cout << user.name;  // Избыточные права доступа
}

// Неконстантный метод, который не меняет состояние
class BankAccount {
public:
    double getBalance() {  // Должен быть const
        return balance;
    }
};

// Изменяемые глобальные данные
char* VERSION = "1.0.0";  // Лучше сделать const

// Неправильное использование mutable
class Wrong {
    mutable int data_;  // mutable для обычных данных - плохая практика
public:
    void setData(int x) const {  // Нарушение логической константности
        data_ = x;
    }
};
```

## Нюансы использования

### 1. Логическая vs Битовая константность
- Логическая: данные не меняются с точки зрения пользователя
- Битовая: физические биты памяти не меняются
- Используй `mutable` для логически константных, но битово изменяемых членов (например, кэш)

### 2. const_cast
- Избегай использования `const_cast`
- Применяй только когда работаешь с legacy API
- Использование `const_cast` для модификации const объекта = UB

### 3. Возвращаемые значения
- Возвращай const для указателей/ссылок на внутренние данные
- Для возврата по значению const обычно избыточен

### 4. West const vs East const
```cpp
const int* p1;  // указатель на константные данные (East)
int const* p2;  // то же самое (West)
// Выбери один стиль и придерживайся его
```

### 5. Константные итераторы
```cpp
for (const auto& item : container) {  // Используй для read-only доступа
    // item нельзя изменить
}
```

### 6. Создание итераторов
```cpp
class Container {
public:
    // Объявление типов итераторов
    using iterator = std::vector<int>::iterator;
    using const_iterator = std::vector<int>::const_iterator;
    
    // Неконстантный итератор
    iterator begin() { return data_.begin(); }
    iterator end() { return data_.end(); }

    // Константный итератор для константных объектов
    const_iterator begin() const { return data_.begin(); }
    const_iterator end() const { return data_.end(); }

    // Константный итератор для неконстантных объектов (C++11)
    const_iterator cbegin() const { return data_.begin(); }
    const_iterator cend() const { return data_.end(); }
private:
    std::vector<int> data_;
};
```

### 7. Перегрузка операторов для константных объектов
```cpp
class Vector {
    double x_, y_;
public:
    // Константные операторы для неизменяемых операций
    Vector operator+(const Vector& other) const {
        return Vector(x_ + other.x_, y_ + other.y_);
    }
    
    Vector operator-(const Vector& other) const {
        return Vector(x_ - other.x_, y_ - other.y_);
    }
    
    // Неконстантные операторы для изменяемых операций
    Vector& operator+=(const Vector& other) {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }
    
    Vector& operator-=(const Vector& other) {
        x_ -= other.x_;
        y_ -= other.y_;
        return *this;
    }
};
```

### 8. Копирование константных объектов
```cpp
class Data {
    int value_;
public:
    // Конструктор копирования может принимать константный объект
    Data(const Data& other) : value_(other.value_) {}
    
    // Оператор присваивания тоже может работать с константным объектом
    Data& operator=(const Data& other) {
        if (this != &other) {
            value_ = other.value_;
        }
        return *this;
    }
    
    // Но сам объект должен быть неконстантным для присваивания
    // Следующий код не скомпилируется:
    // const Data d1, d2;
    // d1 = d2; // Ошибка: нельзя присвоить константному объекту
};
```

### 9. Оператор доступа к элементам
```cpp
class Array {
    std::vector<int> data_;
public:
    // Неконстантная версия - позволяет изменять элементы
    int& operator[](size_t index) {
        return data_[index];
    }
    
    // Константная версия - только для чтения
    const int& operator[](size_t index) const {
        return data_[index];
    }
    
    // Использование:
    // Array arr;
    // arr[0] = 42;        // OK: использует неконстантную версию
    // const Array carr;
    // carr[0] = 42;       // Ошибка: константная версия возвращает const ссылку
    // int x = carr[0];    // OK: можно читать из константного объекта
};
```

### 10. Спецификатор mutable
```cpp
class Cache {
    mutable std::mutex mutex_;        // Для синхронизации в const методах
    mutable size_t access_count_ = 0; // Для статистики
    std::map<Key, Value> data_;       // Основные данные - не mutable

public:
    Value get(const Key& key) const {
        std::lock_guard<std::mutex> lock(mutex_); // OK благодаря mutable
        ++access_count_;                          // OK благодаря mutable
        return data_.at(key);                     // Только чтение data_
    }
};
```

#### Когда использовать mutable:
- Для кэширования результатов
- Для ведения статистики/логов
- Для синхронизации (мьютексы)
- Для ленивой инициализации

#### Когда НЕ использовать mutable:
- Для обхода константности основных данных
- Когда изменения видны пользователю класса
- Для изменения наблюдаемого состояния объекта