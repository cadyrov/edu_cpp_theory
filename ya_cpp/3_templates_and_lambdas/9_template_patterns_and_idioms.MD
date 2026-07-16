# 9. Паттерны и идиомы шаблонов

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

### Пример 2: общий тип

`std::common_type_t<T, U>` выбирает общий тип, к которому можно привести оба типа.

```cpp
#include <type_traits>

template <typename T, typename U>
std::common_type_t<T, U> add(T a, U b) {
    return a + b;
}
```

Например, для `int` и `double` общим типом будет `double`.

```cpp
auto x = add(1, 2.5); // double
```

Это полезно, когда тип результата хочется зафиксировать явно, а не оставлять только на `auto`.

### Пример 3: if constexpr

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

### Пример 4: tag dispatch

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

### Пример 5: compile-time вычисление

Шаблоны могут считать значения на этапе компиляции.

```cpp
#include <cstddef>

template <std::size_t N>
struct Fibonacci {
    static const unsigned value =
        Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template <>
struct Fibonacci<0> {
    static const unsigned value = 0;
};

template <>
struct Fibonacci<1> {
    static const unsigned value = 1;
};

int main() {
    static_assert(Fibonacci<6>::value == 8);
}
```

`Fibonacci<N>` рекурсивно обращается к `Fibonacci<N - 1>` и `Fibonacci<N - 2>`.

Специализации `Fibonacci<0>` и `Fibonacci<1>` нужны как база рекурсии.
Без них компилятор продолжил бы инстанцировать шаблоны дальше.

Сейчас для таких задач чаще используют `constexpr`-функции, но пример хорошо показывает, что шаблон может порождать разные типы и значения во время компиляции.

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

Рекурсивным шаблонам нужна база.

```cpp
template <std::size_t N>
struct Fibonacci {
    static const unsigned value =
        Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};
```

Без специализаций для `0` и `1` такая рекурсия не остановится.

## Саммари

- `type traits` дают информацию о типах.
- `std::common_type_t<T, U>` помогает выбрать общий тип для двух типов.
- `static_assert` проверяет ограничения на этапе компиляции.
- `if constexpr` выбирает код для конкретного типа.
- `tag dispatch` выбирает реализацию через тип-тег.
- Шаблоны могут выполнять compile-time вычисления.
- Шаблоны полезны для обобщенного кода.
- Главный риск - сложные ошибки и переусложнение.
