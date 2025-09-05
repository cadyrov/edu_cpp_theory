# SFINAE и Type Traits

## Определение
SFINAE (Substitution Failure Is Not An Error) - принцип C++, при котором ошибки подстановки типов в шаблонах не являются ошибками компиляции, а используются для выбора перегрузки функции.
Type Traits - шаблонные классы для получения информации о типах во время компиляции.

## Зачем это нужно
- Выбор правильной перегрузки функции на этапе компиляции
- Проверка свойств типов
- Условная компиляция кода
- Метапрограммирование
- Оптимизация на основе типов

## Примеры

### ✅ Хорошо
```cpp
// SFINAE для проверки наличия метода
template<typename T>
auto process(T& obj) -> decltype(obj.handle(), void()) {
    obj.handle();  // Вызывается если метод существует
}

template<typename T>
void process(T&) {
    // Fallback для типов без метода handle()
}

// Type traits для специализации
template<typename T>
std::enable_if_t<std::is_integral_v<T>, T>
increment(T value) {
    return value + 1;
}

// Проверка нескольких условий
template<typename T>
using EnableIfStringLike = std::enable_if_t<
    std::is_convertible_v<T, std::string_view>
>;

// Условная компиляция
template<typename T>
struct Container {
    void optimize() {
        if constexpr (std::is_trivially_copyable_v<T>) {
            // Быстрая оптимизация для простых типов
        } else {
            // Общий случай
        }
    }
};
```

### ❌ Плохо
```cpp
// Сложная для понимания SFINAE
template<typename T,
    typename = typename std::enable_if<
        !std::is_same<
            typename std::decay<T>::type,
            typename std::decay<
                decltype(std::declval<T>().foo())
            >::type
        >::value
    >::type
>
void complex_function(T&& t);  // Слишком сложно

// Неправильное использование type traits
template<typename T>
void process(T value) {
    if (std::is_pointer_v<T>) {  // Runtime check вместо compile-time
        // ...
    }
}

// Избыточное использование SFINAE
template<typename T>
auto simple_function(T x) 
    -> typename std::enable_if<std::is_integral<T>::value, T>::type
{
    return x;  // Лучше использовать concepts
}
```

## Нюансы использования

### 1. Базовые type traits
```cpp
// Проверка категорий типов
static_assert(std::is_integral_v<int>);
static_assert(std::is_floating_point_v<double>);
static_assert(std::is_pointer_v<int*>);

// Модификаторы типов
using Type = std::remove_pointer_t<int*>;  // int
using Const = std::add_const_t<int>;      // const int
```

### 2. SFINAE с enable_if
```cpp
// На возвращаемом типе
template<typename T>
std::enable_if_t<std::is_arithmetic_v<T>, T>
safe_divide(T a, T b) {
    return b != 0 ? a / b : T{};
}

// На дополнительном параметре
template<typename T,
    std::enable_if_t<std::is_class_v<T>>* = nullptr>
void process(T& obj);
```

### 3. Void_t
```cpp
// Проверка наличия типа
template<typename T, typename = void>
struct has_type_member : std::false_type {};

template<typename T>
struct has_type_member<T, 
    std::void_t<typename T::type>> : std::true_type {};
```

### 4. Decltype и declval
```cpp
// Проверка вызываемости
template<typename T>
auto call_if_possible(T& obj)
    -> decltype(obj.call(), void()) {
    obj.call();
}

// Fallback
template<typename T>
void call_if_possible(T&) { }
```

### 5. Conditional
```cpp
template<typename T>
using Number = std::conditional_t<
    std::is_integral_v<T>,
    int64_t,    // Для целых
    double      // Для остальных
>;
```

### 6. Type categories
```cpp
// Проверка категорий значений
template<typename T>
void process(T&& t) {
    if constexpr (std::is_lvalue_reference_v<T>) {
        // L-value
    } else {
        // R-value
    }
}
```

### 7. Custom type traits
```cpp
// Собственный type trait
template<typename T, typename = void>
struct has_serialize : std::false_type {};

template<typename T>
struct has_serialize<T,
    std::void_t<decltype(std::declval<T>().serialize())>
> : std::true_type {};

// Использование
template<typename T>
std::enable_if_t<has_serialize<T>::value>
save(const T& obj) {
    obj.serialize();
}
```

### 8. Compile-time проверки
```cpp
// Статические проверки
static_assert(std::is_default_constructible_v<MyType>,
    "MyType must be default constructible");

// Условная компиляция
if constexpr (std::is_trivially_copyable_v<T>) {
    std::memcpy(dst, src, sizeof(T));
} else {
    copy_element(dst, src);
}
```
