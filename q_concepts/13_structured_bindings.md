# Structured Bindings

## Определение
Structured Bindings (C++17) - синтаксическая возможность, позволяющая удобно распаковывать кортежи, пары, структуры и массивы в отдельные именованные переменные.

## Зачем это нужно
- Более чистый и читаемый код
- Удобная работа с составными типами
- Уменьшение вероятности ошибок
- Улучшение производительности (избегание копирований)
- Более идиоматический C++ код

## Примеры

### ✅ Хорошо
```cpp
// Распаковка tuple
std::tuple<int, std::string, double> getData() {
    return {1, "test", 3.14};
}
auto [id, name, value] = getData();

// Работа с map
std::map<std::string, int> scores;
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << '\n';
}

// Структуры
struct Point {
    double x, y, z;
};
Point getPoint();
auto [x, y, z] = getPoint();

// Массивы фиксированной длины
int arr[] = {1, 2, 3};
auto [a, b, c] = arr;

// Возврат нескольких значений
struct QueryResult {
    bool success;
    std::string data;
    int error_code;
};
if (auto [ok, data, error] = performQuery(); ok) {
    process(data);
} else {
    handleError(error);
}
```

### ❌ Плохо
```cpp
// Игнорирование const
const auto [x, y] = getPoint();
x = 42;  // Ошибка компиляции

// Неправильные имена
auto [a, b, c] = getPersonInfo();  // Неинформативные имена

// Избыточное копирование
auto [heavy1, heavy2] = getHeavyObjects();  // Лучше const auto&

// Частичная деструктуризация
std::pair<int, std::string> pair = {1, "test"};
auto [num, _] = pair;  // Нельзя пропускать значения
```

## Нюансы использования

### 1. Ссылки и const
```cpp
// Различные квалификаторы
const auto& [x, y] = point;     // Константная ссылка
auto&& [name, age] = getPerson();  // Универсальная ссылка
```

### 2. Типы привязок
```cpp
struct S {
    int x;
    std::string str;
};
S s;
auto [x, str] = s;       // x: int, str: std::string
const auto& [rx, rstr] = s;  // rx: const int&, rstr: const std::string&
```

### 3. Lifetime
```cpp
// Время жизни временных объектов
if (auto [iter, inserted] = map.insert(value); inserted) {
    // iter и inserted живут только в if
}
```

### 4. Кастомные типы
```cpp
struct Custom {
    template<std::size_t I>
    auto get() const {
        if constexpr (I == 0) return x;
        else if constexpr (I == 1) return y;
    }
    int x;
    double y;
};
// Специализации для поддержки structured bindings
namespace std {
    template<> struct tuple_size<Custom> 
        : std::integral_constant<std::size_t, 2> {};
    
    template<std::size_t I> 
    struct tuple_element<I, Custom> {
        using type = decltype(std::declval<Custom>().template get<I>());
    };
}
```

### 5. Ограничения
```cpp
// Нельзя с динамическими массивами
int* arr = new int[3]{1, 2, 3};
auto [x, y, z] = arr;  // Ошибка

// Нельзя частично деструктурировать
struct S { int a, b, c; };
auto [x, y] = S{1, 2, 3};  // Ошибка: нужны все поля
```

### 6. В циклах
```cpp
std::vector<std::pair<std::string, int>> data;
// Range-based for с structured binding
for (const auto& [name, value] : data) {
    // Используем name и value напрямую
}
```

### 7. С алгоритмами
```cpp
std::map<std::string, int> data;
// Использование в алгоритмах
std::for_each(data.begin(), data.end(),
    [](const auto& [key, value]) {
        std::cout << key << ": " << value << '\n';
    });
```

### 8. В лямбдах
```cpp
auto processor = [](const auto& [name, age, score]) {
    return name + " scored " + std::to_string(score);
};
```
