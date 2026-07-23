# 16. Ограничения и концепты

## Суть

Концепт задает требование к шаблонному параметру.

```cpp
#include <concepts>

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;
```

Ограничения делают шаблонный интерфейс понятнее и дают более точные ошибки компиляции.

`requires` используется в двух смыслах:

- `requires`-выражение проверяет требования и возвращает `bool` на этапе компиляции.
- `requires`-ограничение включает шаблон только при выполнении условия.

## Примеры

### Пример 1: `requires`-выражение

```cpp
#include <concepts>

template <typename T>
inline constexpr bool has_value_type_v = requires {
    typename T::value_type;
};

template <typename T>
inline constexpr bool has_size_v = requires(const T& value) {
    value.size();
};
```

`typename T::value_type` проверяет наличие вложенного типа.
Без `typename` это было бы проверкой выражения `T::value_type`.

### Пример 2: составные требования

```cpp
#include <concepts>
#include <cstddef>

template <typename T>
concept HasExactSize = requires(const T& value) {
    typename T::value_type;
    { value.size() } noexcept -> std::same_as<std::size_t>;
};
```

В фигурных скобках можно проверить тип результата и `noexcept`.

### Пример 3: ограничение через `requires`

```cpp
#include <concepts>

template <typename T>
requires std::integral<T>
bool is_even(T value) {
    return value % 2 == 0;
}
```

Функция доступна только для целочисленных типов.

Ограничение можно поставить и после сигнатуры функции.

```cpp
template <typename T>
bool positive(T value) requires std::signed_integral<T> {
    return value > 0;
}
```

Если нужно сразу написать `requires`-выражение, слово `requires` повторяется:

```cpp
template <typename T>
auto get_size(const T& value) requires requires { value.size(); } {
    return value.size();
}
```

### Пример 4: сокращенная запись

```cpp
#include <concepts>

bool positive(std::signed_integral auto value) {
    return value > 0;
}
```

Так можно ограничить `auto`-параметр.

### Пример 5: собственный концепт

```cpp
#include <concepts>
#include <cstddef>

template <typename T>
concept HasSize = requires(const T& value) {
    { value.size() } -> std::same_as<std::size_t>;
};

template <HasSize T>
std::size_t get_size(const T& value) {
    return value.size();
}
```

`requires`-выражение проверяет, что код корректен для типа `T`.

### Пример 6: концепт с несколькими параметрами

```cpp
#include <concepts>

template <typename T, typename U>
concept AddableTo = requires(T a, U b) {
    { a + b };
};

template <typename T, typename U>
requires AddableTo<T, U>
auto add(T a, U b) {
    return a + b;
}
```

Концепт может иметь несколько типовых, нетиповых или шаблонных параметров.

### Пример 7: `Hashable`

```cpp
#include <concepts>
#include <cstddef>
#include <functional>

template <typename T>
concept Hashable = requires(const T& value) {
    { std::hash<T>{}(value) } -> std::same_as<std::size_t>;
};
```

Так проверяется, что `std::hash<T>` можно вызвать и он возвращает ровно
`std::size_t`.

## Подводные камни

Концепт должен описывать смысловое требование, а не случайную деталь реализации.

```cpp
template <typename T>
concept HasBegin = requires(T x) { x.begin(); };
```

Наличие `begin()` еще не означает, что тип является полноценным диапазоном.

Ограничения участвуют в выборе перегрузки.

```cpp
void f(std::integral auto);
void f(std::signed_integral auto);
```

Для `int` более специфичной будет перегрузка со `std::signed_integral`.

Неудачная подстановка внутри ограничения не является ошибкой: такой шаблон
просто не подходит.

```cpp
template <typename T>
requires(sizeof(typename T::value_type) <= 16)
void g(const T&);

g(42); // эта перегрузка не подходит: у int нет value_type
```

Ограничения можно применять к шаблонам функций, классов, переменных, alias,
шаблонным методам и лямбдам.

Слишком сложные `requires`-выражения ухудшают читаемость.

Если ограничение нужно только внутри тела, иногда достаточно `static_assert`.

## Саммари

- Концепты задают требования к шаблонным параметрам.
- `requires`-выражение проверяет типы, выражения, `noexcept` и тип результата.
- `requires`-ограничение исключает шаблон из рассмотрения, если условие ложно.
- Стандартные концепты лежат в `<concepts>`.
- Концепт можно использовать в `requires`, вместо `typename` и вместе с `auto`.
- Ограничения помогают получать понятные ошибки.
- Более ограниченная перегрузка может выиграть при разрешении перегрузки.
- В C++20 концепты часто заменяют SFINAE в публичном интерфейсе.
