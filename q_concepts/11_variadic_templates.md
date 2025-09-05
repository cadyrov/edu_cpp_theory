# Variadic Templates

## Определение
Вариативные шаблоны - возможность C++ создавать шаблоны классов и функций, принимающие произвольное количество типизированных параметров.

## Зачем это нужно
- Обобщённое программирование с произвольным числом аргументов
- Реализация type-safe вариативных функций
- Создание контейнеров и кортежей
- Оптимизация производительности через compile-time развёртывание
- Реализация паттернов проектирования

## Примеры

### ✅ Хорошо
```cpp
// Рекурсивная сумма
template<typename T>
T sum(T value) {
    return value;
}

template<typename T, typename... Args>
T sum(T first, Args... args) {
    return first + sum(args...);
}

// Идеальная передача аргументов
template<typename... Args>
void forward_all(Args&&... args) {
    process(std::forward<Args>(args)...);
}

// Вариативный класс
template<typename... Types>
class Tuple;

// Фабричная функция
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(
        new T(std::forward<Args>(args)...)
    );
}
```

### ❌ Плохо
```cpp
// Неэффективная рекурсия
template<typename... Args>
void print_all(Args... args) {
    (std::cout << ... << args);  // Используй fold expression
}

// Потеря типов
template<typename... Args>
void wrong(Args... args) {
    process(args...);  // Теряем r-value nature
}

// Избыточная рекурсия
template<typename T, typename... Args>
void over_complex(T first, Args... rest) {
    process(first);
    if constexpr (sizeof...(rest) > 0)
        over_complex(rest...);
    // Лучше использовать fold expression
}
```

## Нюансы использования

### 1. Fold Expressions (C++17)
```cpp
template<typename... Args>
auto sum(Args... args) {
    return (... + args);  // Унарный левый fold
}

template<typename... Args>
void print(Args... args) {
    (std::cout << ... << args);  // Бинарный правый fold
}
```

### 2. sizeof... оператор
```cpp
template<typename... Args>
void check(Args... args) {
    static_assert(sizeof...(Args) > 0, 
                 "Need at least one argument");
    std::cout << "Got " << sizeof...(args) 
              << " arguments\n";
}
```

### 3. Parameter Pack Expansion
```cpp
template<typename... Types>
struct Tuple {
    std::tuple<Types...> data;  // Pack expansion
};

template<typename... Args>
void forward(Args&&... args) {
    // Множественная expansion
    process(std::forward<Args>(args)...);
}
```

### 4. Рекурсивная обработка
```cpp
// Базовый случай
void process() {}

template<typename T, typename... Args>
void process(T&& first, Args&&... rest) {
    handle(std::forward<T>(first));
    process(std::forward<Args>(rest)...);
}
```

### 5. Compile-time проверки
```cpp
template<typename... Args>
void validate() {
    static_assert((std::is_integral_v<Args> && ...), 
                 "All types must be integral");
}
```

### 6. Variadic Using
```cpp
template<typename... Bases>
struct Derived : Bases... {
    using Bases::operator()...;  // Inherit all operators
};
```

### 7. Variadic Templates с SFINAE
```cpp
template<typename T, typename... Args,
         std::enable_if_t<std::is_constructible_v<T, Args...>>* = nullptr>
T make(Args&&... args) {
    return T(std::forward<Args>(args)...);
}
```

### 8. Variadic Class Templates
```cpp
template<typename... Types>
class MultiContainer : public std::vector<Types>... {
public:
    // Наследование конструкторов
    using std::vector<Types>::vector...;
};
```
