# Concepts

## Определение
Concepts (C++20) - механизм для задания требований к шаблонным параметрам, который позволяет писать более понятные ограничения и получать более читаемые сообщения об ошибках.

## Зачем это нужно
- Улучшение читаемости шаблонного кода
- Более понятные сообщения об ошибках
- Замена сложного SFINAE
- Документирование требований к типам
- Упрощение разработки обобщённых компонентов

## Примеры

### ✅ Хорошо
```cpp
// Базовый concept
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

// Использование concept
template<Numeric T>
T add(T a, T b) {
    return a + b;
}

// Составной concept
template<typename T>
concept Sortable = requires(T& container) {
    { container.begin() } -> std::same_as<typename T::iterator>;
    { container.end() } -> std::same_as<typename T::iterator>;
    requires std::totally_ordered<typename T::value_type>;
};

// Concept с несколькими требованиями
template<typename T>
concept Streamable = requires(std::ostream& os, const T& value) {
    { os << value } -> std::same_as<std::ostream&>;
};

// Использование стандартных concepts
template<std::integral T>
T gcd(T a, T b) {
    while (b != 0) {
        T temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
```

### ❌ Плохо
```cpp
// Слишком общий concept
template<typename T>
concept Any = true;  // Бесполезное ограничение

// Избыточные проверки
template<typename T>
concept TooComplex = requires(T x) {
    requires std::is_class_v<T>;
    requires std::is_default_constructible_v<T>;
    requires std::is_copy_constructible_v<T>;
    // Лучше разбить на отдельные concepts
};

// Неправильное использование requires
template<typename T>
concept Wrong = requires(T x) {
    x.some_method();  // Не проверяет возвращаемый тип
};
```

## Нюансы использования

### 1. Requires expressions
```cpp
// Простое требование
template<typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};

// Составное требование
template<typename T>
concept Container = requires(T c) {
    typename T::value_type;
    typename T::iterator;
    { c.begin() } -> std::same_as<typename T::iterator>;
    { c.size() } -> std::convertible_to<std::size_t>;
};
```

### 2. Conjunction of concepts
```cpp
template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

template<typename T>
concept Number = Numeric<T> && Addable<T>;
```

### 3. Constrained class templates
```cpp
template<typename T>
    requires std::default_initializable<T>
class Buffer {
    T data_;
public:
    Buffer() = default;
};

// Альтернативный синтаксис
template<std::default_initializable T>
class Buffer {
    // ...
};
```

### 4. Constrained auto
```cpp
void process(std::integral auto value) {
    // Работает только с целыми числами
}

void print(std::convertible_to<std::string_view> auto const& text) {
    std::cout << text << '\n';
}
```

### 5. Concept overloading
```cpp
template<typename T>
concept Incrementable = requires(T x) {
    { ++x } -> std::same_as<T&>;
};

void advance(Incrementable auto& x) {
    ++x;
}

void advance(std::integral auto& x) {
    x += 1;
}
```

### 6. Nested requirements
```cpp
template<typename T>
concept Resizable = requires(T container) {
    { container.resize(0) };
    requires std::same_as<decltype(container.size()), std::size_t>;
};
```

### 7. Standard concepts
```cpp
// Из <concepts>
template<std::regular T>
class Container {
    // Требует regular type
};

template<std::ranges::random_access_range R>
void algorithm(R& range) {
    // Требует random access range
}
```

### 8. Best practices
```cpp
// 1. Атомарные concepts
template<typename T>
concept Addable = requires(T a, T b) { { a + b }; };

template<typename T>
concept Subtractable = requires(T a, T b) { { a - b }; };

// 2. Композиция concepts
template<typename T>
concept Arithmetic = Addable<T> && Subtractable<T>;

// 3. Документирование
/// Requires: T must support addition and multiplication
template<typename T>
    requires Arithmetic<T>
T square(T x) {
    return x * x;
}
```

### 9. Constraints vs Concepts
```cpp
// Предпочтительно
template<std::integral T>
void func(T value);

// Менее предпочтительно
template<typename T>
    requires std::integral<T>
void func(T value);
```
