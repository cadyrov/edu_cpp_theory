# 8. Паттерны и идиомы шаблонов

## Суть

Шаблоны используют не только для контейнеров.

С их помощью пишут проверки типов, адаптеры, compile-time вычисления и общий код без виртуальных функций.

## Примеры

### Пример 1: type traits

```cpp
#include <type_traits>

template <typename T>
void print_number(T value) {
    static_assert(std::is_arithmetic_v<T>);
    std::cout << value << '\n';
}
```

`type traits` отвечают на вопросы о типах.

### Пример 2: if constexpr

```cpp
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

Ненужная ветка не компилируется для конкретного `T`.

### Пример 3: tag dispatch

```cpp
#include <iterator>

template <typename Iterator>
void advance_impl(Iterator& it, int n, std::random_access_iterator_tag) {
    it += n;
}

template <typename Iterator>
void advance_impl(Iterator& it, int n, std::input_iterator_tag) {
    while (n-- > 0) {
        ++it;
    }
}
```

Выбор реализации идет через тип-тег.

## Подводные камни

`static_assert` должен давать понятную ошибку.

```cpp
static_assert(std::is_integral_v<T>, "T must be integral");
```

Слишком общий шаблон может дать длинную ошибку компиляции.

```cpp
template <typename T>
void save(T value) {
    value.serialize();
}
```

Если у `T` нет `serialize`, ошибка может быть далеко от места вызова.

`if constexpr` проверяет условие во время компиляции, но условие должно зависеть от шаблона.

```cpp
if constexpr (std::is_pointer_v<T>) {
}
```

Шаблоны легко усложнить. Если обычная функция решает задачу, шаблон не нужен.

## Саммари

- `type traits` дают информацию о типах.
- `static_assert` проверяет ограничения на этапе компиляции.
- `if constexpr` выбирает код для конкретного типа.
- `tag dispatch` выбирает реализацию через тип-тег.
- Шаблоны полезны для обобщенного кода.
- Главный риск - сложные ошибки и переусложнение.
