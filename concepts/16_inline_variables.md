# Inline Variables

## Определение
Inline variables (C++17) - переменные, которые могут быть определены в нескольких единицах трансляции без нарушения ODR (One Definition Rule), аналогично inline функциям.

## Зачем это нужно
- Определение констант в заголовочных файлах
- Thread-safe инициализация глобальных переменных
- Улучшение модульности кода
- Избежание проблем с ODR
- Упрощение работы с шаблонами

## Примеры

### ✅ Хорошо
```cpp
// В заголовочном файле
// constants.h
inline constexpr int MAX_SIZE = 100;
inline const std::string VERSION = "1.0.0";

// Статические члены класса
class Widget {
    static inline int count_ = 0;
    inline static const int MAX_WIDGETS = 1000;
};

// Thread-safe синглтон
class Singleton {
public:
    static Singleton& instance() {
        static inline Singleton instance;
        return instance;
    }
};

// Константы в namespace
namespace config {
    inline constexpr double PI = 3.14159265359;
    inline const std::string APP_NAME = "MyApp";
}
```

### ❌ Плохо
```cpp
// Определение не-const переменных
inline int counter = 0;  // Плохая идея для мутабельных данных

// Избыточное использование inline
class Bad {
    inline static int simple_ = 42;  // inline не нужен для простых типов
};

// Неправильное использование с extern
extern inline int global;  // extern и inline конфликтуют

// ODR нарушение
// header.h
static int value = 42;  // Лучше использовать inline
```

## Нюансы использования

### 1. ODR и линковка
```cpp
// foo.h
inline const std::string APP_VERSION = "1.0.0";

// Можно включать в multiple translation units
// foo.cpp и bar.cpp могут включать foo.h
```

### 2. Статические члены класса
```cpp
class Counter {
    // До C++17
    static const int MAX = 100;  // Объявление
    // Требовалось определение в .cpp файле
    
    // C++17
    static inline const int MAX = 100;  // Объявление и определение
    static inline int count_ = 0;
};
```

### 3. Constexpr переменные
```cpp
// constexpr автоматически inline
constexpr int BUFFER_SIZE = 1024;  // Неявно inline

// Явное указание может улучшить читаемость
inline constexpr int BUFFER_SIZE = 1024;
```

### 4. Thread Safety
```cpp
class Logger {
    static Logger& instance() {
        static inline Logger instance_;  // Thread-safe инициализация
        return instance_;
    }
};
```

### 5. Шаблоны и inline
```cpp
template<typename T>
class Container {
    static inline std::size_t count_ = 0;  // Для каждой инстанциации
    inline static const T default_value_{};
};
```

### 6. Namespace scope
```cpp
namespace config {
    // Константы уровня namespace
    inline constexpr struct {
        int max_connections = 100;
        int timeout_ms = 5000;
    } network_settings;
}
```

### 7. Best practices
```cpp
// 1. Используй для констант в заголовках
inline constexpr int MAX_RETRY = 3;

// 2. Для сложных типов с non-trivial конструкторами
inline const std::regex IP_REGEX(
    "^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$"
);

// 3. Для статических членов класса
class Config {
    static inline const std::string DEFAULT_CONFIG = "config.json";
};
```

### 8. Ограничения
```cpp
// Нельзя использовать с:
extern inline int value;  // Конфликт спецификаторов

// Осторожно с:
inline int counter = 0;  // Мутабельные данные
// Может привести к проблемам синхронизации
```
