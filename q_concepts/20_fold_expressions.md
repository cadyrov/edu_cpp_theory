# Fold Expressions

## Определение
Fold Expressions (C++17) - синтаксическая конструкция, позволяющая применять бинарные операторы к parameter packs в шаблонах, упрощая работу с вариативными шаблонами.

## Зачем это нужно
- Упрощение работы с parameter packs
- Более компактный и читаемый код
- Уменьшение шаблонной рекурсии
- Элегантная обработка множества аргументов
- Улучшение производительности компиляции

## Примеры

### ✅ Хорошо
```cpp
// Сумма всех аргументов
template<typename... Args>
auto sum(Args... args) {
    return (... + args);  // Унарный левый fold
}

// Вывод всех аргументов
template<typename... Args>
void print(Args... args) {
    (std::cout << ... << args) << '\n';
}

// Проверка всех условий
template<typename... Args>
bool all(Args... args) {
    return (... && args);
}

// Вызов методов для всех объектов
template<typename... Objects>
void process(Objects&... objects) {
    (objects.process(), ...);
}

// Инициализация с помощью fold
template<typename T, typename... Args>
void push_all(std::vector<T>& vec, Args&&... args) {
    (vec.push_back(std::forward<Args>(args)), ...);
}
```

### ❌ Плохо
```cpp
// Избыточная рекурсия вместо fold
template<typename T>
T sum_recursive(T value) {
    return value;
}

template<typename T, typename... Args>
T sum_recursive(T first, Args... args) {
    return first + sum_recursive(args...);  // Используй fold

// Неправильный порядок операций
template<typename... Args>
void wrong_print(Args... args) {
    (args << ... << std::cout);  // Неправильный порядок
}

// Смешивание разных типов без преобразования
template<typename... Args>
auto unsafe_sum(Args... args) {
    return (args + ...);  // Может привести к неожиданным результатам
}
```

## Нюансы использования

### 1. Типы fold expressions
```cpp
template<typename... Args>
void demo(Args... args) {
    // Унарный правый fold
    (args + ...)     // ((a1 + a2) + a3)

    // Унарный левый fold
    (... + args)     // (a1 + (a2 + a3))

    // Бинарный правый fold
    (args + ... + 0) // ((a1 + a2) + (a3 + 0))

    // Бинарный левый fold
    (0 + ... + args) // (0 + (a1 + (a2 + a3)))
}
```

### 2. Операторы для fold
```cpp
// Арифметические
(... + args)  // Сложение
(... * args)  // Умножение

// Логические
(... && args) // Логическое И
(... || args) // Логическое ИЛИ

// Побитовые
(... | args)  // Побитовое ИЛИ
(... & args)  // Побитовое И

// Сравнения
(... < args)  // Меньше
(... == args) // Равно
```

### 3. Пустые parameter packs
```cpp
template<typename... Args>
bool all(Args... args) {
    return (... && args);    // true для пустого pack
}

template<typename... Args>
bool any(Args... args) {
    return (... || args);    // false для пустого pack
}
```

### 4. Комбинирование с другими выражениями
```cpp
template<typename... Args>
void complex_fold(Args... args) {
    // С вызовом функции
    (process(args), ...);

    // С условным оператором
    ((args > 0 ? process(args) : ignore(args)), ...);
}
```

### 5. Fold с запятой
```cpp
template<typename... Args>
void multi_action(Args... args) {
    // Несколько действий
    ((std::cout << args << " "), ...);
    
    // Инициализация нескольких объектов
    std::tuple objects{(std::make_unique<Args>(), ...)};
}
```

### 6. Fold для вызова методов
```cpp
class Widget {
public:
    void update() { }
};

template<typename... Widgets>
void update_all(Widgets&... widgets) {
    (widgets.update(), ...);
}
```

### 7. Fold в constexpr контексте
```cpp
template<typename... Args>
constexpr auto sum_constexpr(Args... args) {
    return (... + args);
}

static_assert(sum_constexpr(1, 2, 3) == 6);
```

### 8. Best practices
```cpp
// 1. Используй скобки для ясности
template<typename... Args>
void clear(Args&... args) {
    (args.clear(), ...);  // Лучше чем args.clear()...
}

// 2. Правильный порядок операций
template<typename... Args>
void print_all(Args&&... args) {
    ((std::cout << args << " "), ...) << '\n';
}

// 3. Обработка ошибок
template<typename... Args>
bool try_process(Args&&... args) {
    return (try_handle(std::forward<Args>(args)) && ...);
}
```
