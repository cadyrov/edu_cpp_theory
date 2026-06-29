# 14. SFINAE

## Суть

SFINAE означает `Substitution Failure Is Not An Error`.

Если при подстановке шаблонных аргументов сигнатура становится некорректной, компилятор не выдает ошибку сразу, а просто убирает эту перегрузку из набора кандидатов.

```cpp
template <typename T>
auto size_of(const T& value) -> decltype(value.size()) {
    return value.size();
}
```

Так можно включать функцию только для типов, у которых есть нужная операция.

## Примеры

### Пример 1: проверка через `std::enable_if`

```cpp
#include <type_traits>

template <typename T>
std::enable_if_t<std::is_integral_v<T>, bool>
is_even(T value) {
    return value % 2 == 0;
}
```

Функция доступна только для целочисленных типов.

### Пример 2: выбор перегрузки

```cpp
#include <iostream>
#include <type_traits>

template <typename T>
std::enable_if_t<std::is_pointer_v<T>>
print(T value) {
    std::cout << *value << '\n';
}

template <typename T>
std::enable_if_t<!std::is_pointer_v<T>>
print(T value) {
    std::cout << value << '\n';
}
```

Одна перегрузка работает для указателей, другая - для остальных типов.

### Пример 3: detection idiom

```cpp
#include <type_traits>
#include <utility>

template <typename, typename = void>
struct HasSize : std::false_type {};

template <typename T>
struct HasSize<T, std::void_t<decltype(std::declval<T>().size())>>
    : std::true_type {};
```

`std::void_t` помогает проверить, существует ли выражение.

## Подводные камни

SFINAE работает только в контексте подстановки шаблонных параметров.

```cpp
template <typename T>
void f() {
    typename T::type x; // ошибка уже внутри тела функции
}
```

Ошибки в теле функции не являются SFINAE.

`enable_if` может сделать сигнатуру трудной для чтения.

```cpp
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
void f(T value);
```

В C++20 для новых интерфейсов чаще используют концепты.

SFINAE может давать сложные ошибки компиляции, особенно при цепочке шаблонов.

## Саммари

- SFINAE убирает неподходящую перегрузку без ошибки компиляции.
- `std::enable_if_t` включает шаблон по условию.
- `std::void_t` удобен для проверки существования выражений.
- SFINAE работает в сигнатуре, а не в теле функции.
- В C++20 концепты обычно читаются лучше.
