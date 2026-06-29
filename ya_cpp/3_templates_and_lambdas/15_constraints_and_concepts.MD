# 15. Ограничения и концепты

## Суть

Концепт задает требование к шаблонному параметру.

```cpp
#include <concepts>

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;
```

Ограничения делают шаблонный интерфейс понятнее и дают более точные ошибки компиляции.

## Примеры

### Пример 1: `requires`

```cpp
#include <concepts>

template <typename T>
requires std::integral<T>
bool is_even(T value) {
    return value % 2 == 0;
}
```

Функция доступна только для целочисленных типов.

### Пример 2: сокращенная запись

```cpp
#include <concepts>

bool positive(std::signed_integral auto value) {
    return value > 0;
}
```

Так можно ограничить `auto`-параметр.

### Пример 3: собственный концепт

```cpp
#include <concepts>

template <typename T>
concept HasSize = requires(T value) {
    { value.size() } -> std::convertible_to<std::size_t>;
};

template <HasSize T>
std::size_t get_size(const T& value) {
    return value.size();
}
```

`requires`-выражение проверяет, что код корректен для типа `T`.

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

Слишком сложные `requires`-выражения ухудшают читаемость.

Если ограничение нужно только внутри тела, иногда достаточно `static_assert`.

## Саммари

- Концепты задают требования к шаблонным параметрам.
- `requires` ограничивает шаблон или проверяет выражения.
- Стандартные концепты лежат в `<concepts>`.
- Ограничения помогают получать понятные ошибки.
- В C++20 концепты часто заменяют SFINAE в публичном интерфейсе.
