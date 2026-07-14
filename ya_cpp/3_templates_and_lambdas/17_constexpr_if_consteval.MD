# 17. Основы constexpr, if constexpr и немедленные функции

## Суть

`constexpr` позволяет вычислять значение во время компиляции, если аргументы известны на этапе компиляции.

```cpp
constexpr int square(int x) {
    return x * x;
}

static_assert(square(5) == 25);
```

`if constexpr` выбирает ветку во время компиляции.

Немедленная функция с `consteval` обязана вычисляться на этапе компиляции.

## Примеры

### Пример 1: `constexpr` функция

```cpp
constexpr int factorial(int n) {
    int result = 1;

    for (int i = 2; i <= n; ++i) {
        result *= i;
    }

    return result;
}

static_assert(factorial(5) == 120);
```

Такую функцию можно использовать и во время компиляции, и во время выполнения.

### Пример 2: `if constexpr`

```cpp
#include <iostream>
#include <type_traits>

template <typename T>
void print(T value) {
    if constexpr (std::is_pointer_v<T>) {
        std::cout << *value << '\n';
    } else {
        std::cout << value << '\n';
    }
}
```

Неподходящая ветка отбрасывается для конкретного `T`.

### Пример 3: `consteval`

```cpp
consteval int checked_square(int x) {
    return x * x;
}

constexpr int value = checked_square(7);
```

Вызов `checked_square` должен быть вычислен во время компиляции.

## Подводные камни

`constexpr` не гарантирует compile-time вычисление при каждом вызове.

```cpp
int x = 10;
int y = square(x); // может быть runtime
```

Для обязательного compile-time вызова используют `consteval`.

`if constexpr` отбрасывает ветку только когда условие известно во время компиляции.

```cpp
if constexpr (std::is_integral_v<T>) {
}
```

Условие обычно зависит от шаблонного параметра.

Отброшенная ветка не инстанцируется, но синтаксически код все равно должен быть корректным.

`consteval` нельзя вызвать с runtime-значением.

```cpp
int x = 5;
auto y = checked_square(x); // ошибка
```

## Саммари

- `constexpr` разрешает compile-time вычисления.
- `constexpr` функция может выполняться и во время выполнения.
- `if constexpr` выбирает ветку на этапе компиляции.
- Отброшенная ветка `if constexpr` не инстанцируется.
- `consteval` требует немедленного compile-time вычисления.
