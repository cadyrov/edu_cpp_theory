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

Fold expressions позволяют применять бинарные операторы к parameter pack без рекурсии. Это более эффективно и читаемо, чем рекурсивные шаблоны.

#### Типы fold expressions

**1. Унарный левый fold** `(... op pack)`
```cpp
template<typename... Args>
auto sum(Args... args) {
    return (... + args);  // ((a1 + a2) + a3) + a4
}

// Примеры
sum(1, 2, 3, 4);  // ((1 + 2) + 3) + 4 = 10

template<typename... Args>
bool all_true(Args... args) {
    return (... && args);  // ((a1 && a2) && a3) && a4
}
```

**2. Унарный правый fold** `(pack op ...)`
```cpp
template<typename... Args>
auto subtract(Args... args) {
    return (args - ...);  // a1 - (a2 - (a3 - a4))
}

// Примеры
subtract(10, 2, 1);  // 10 - (2 - 1) = 9
```

**3. Бинарный левый fold** `(init op ... op pack)`
```cpp
template<typename... Args>
auto sum_with_init(int init, Args... args) {
    return (init + ... + args);  // ((init + a1) + a2) + a3
}

// Примеры
sum_with_init(10, 1, 2, 3);  // ((10 + 1) + 2) + 3 = 16

template<typename... Args>
void print_all(Args... args) {
    (std::cout << ... << args);  // std::cout << a1 << a2 << a3
}
```

**4. Бинарный правый fold** `(pack op ... op init)`
```cpp
template<typename... Args>
auto subtract_from(int init, Args... args) {
    return (args - ... - init);  // a1 - (a2 - (a3 - init))
}
```

#### Поддерживаемые операторы

**Арифметические**: `+`, `-`, `*`, `/`, `%`
```cpp
template<typename... Args>
auto multiply(Args... args) {
    return (... * args);  // a1 * a2 * a3 * ...
}
```

**Логические**: `&&`, `||`
```cpp
template<typename... Args>
bool all(Args... args) {
    return (... && args);  // Все должны быть true
}

template<typename... Args>
bool any(Args... args) {
    return (... || args);  // Хотя бы один true
}
```

**Битовые**: `&`, `|`, `^`
```cpp
template<typename... Args>
auto bitwise_or(Args... args) {
    return (... | args);
}
```

**Сравнение**: `==`, `!=`, `<`, `>`, `<=`, `>=`
```cpp
template<typename... Args>
bool all_equal(Args... args) {
    return ((args == ... == args));  // Проверка всех на равенство
}
```

**Оператор запятой**: `,`
```cpp
template<typename... Args>
void execute_all(Args... args) {
    (..., args());  // Выполнить все функции по порядку
}

// Инициализация нескольких объектов
template<typename... Args>
void init_all(Args&... args) {
    ((args = {}), ...);  // args1 = {}, args2 = {}, ...
}
```

**Оператор доступа к члену**: `->*`, `.*`
```cpp
template<typename Obj, typename... Funcs>
auto call_all(Obj& obj, Funcs... funcs) {
    return ((obj.*funcs)(), ...);  // Вызвать все методы
}
```

#### Пустые fold expressions

Для унарных fold с операторами `&&`, `||`, `,` определено поведение для пустого pack:

```cpp
template<typename... Args>
bool all() {
    return (... && Args{});  // true для пустого pack
}

template<typename... Args>
bool any() {
    return (... || Args{});  // false для пустого pack
}

template<typename... Args>
void do_nothing() {
    (..., Args{});  // Ничего не делает для пустого pack
}
```

Для других операторов пустой pack вызовет ошибку компиляции.

#### Практические примеры

```cpp
// Проверка всех типов на условие
template<typename... Args>
constexpr bool all_integral() {
    return (std::is_integral_v<Args> && ...);
}

// Вызов функции для каждого аргумента
template<typename Func, typename... Args>
void for_each(Func&& f, Args&&... args) {
    (f(std::forward<Args>(args)), ...);
}

// Создание кортежа с проверкой типов
template<typename... Args>
auto make_checked_tuple(Args&&... args) {
    static_assert((std::is_copy_constructible_v<Args> && ...),
                  "All types must be copy constructible");
    return std::tuple<Args...>(std::forward<Args>(args)...);
}

// Логирование с разделителями
template<typename... Args>
void log_with_separator(const char* sep, Args&&... args) {
    bool first = true;
    ((std::cout << (first ? (first = false, "") : sep) 
                << std::forward<Args>(args)), ...);
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
