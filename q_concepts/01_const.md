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

### 6. Спецификатор mutable
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