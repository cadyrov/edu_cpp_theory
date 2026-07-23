# 15. SFINAE

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

SFINAE работает в непосредственном контексте: в типах параметров, возвращаемом
типе и шаблонных параметрах функции. Тело функции сюда не входит.

## Примеры

### Пример 1: неудачная подстановка

```cpp
double f(double) {
    return {};
}

template <typename Container>
typename Container::value_type f(const Container&) {
    return {};
}

auto x = f(42); // выбран f(double), потому что у int нет value_type
```

Если `Container::value_type` перенести в тело функции, SFINAE уже не поможет:
ошибка возникнет после выбора перегрузки.

### Пример 2: проверка через `std::enable_if`

```cpp
#include <type_traits>

template <typename T, std::enable_if_t<std::is_integral_v<T>>* = nullptr>
bool is_even(T value) {
    return value % 2 == 0;
}
```

Функция доступна только для целочисленных типов.

### Пример 3: выбор перегрузки

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

### Пример 4: проверка выражения через `decltype`

```cpp
#include <utility>

template <
    typename Container,
    typename = decltype(std::declval<const Container&>().size())
>
auto size_of(const Container& value) {
    return value.size();
}
```

`std::declval<T>()` используют только в невычисляемом контексте, например внутри
`decltype` или `sizeof`.

### Пример 5: detection idiom

```cpp
#include <type_traits>
#include <utility>

template <typename, typename = void>
struct HasSize : std::false_type {};

template <typename T>
struct HasSize<T, std::void_t<decltype(std::declval<const T&>().size())>>
    : std::true_type {};
```

`std::void_t` помогает проверить, существует ли выражение.

Для удобства обычно добавляют переменную:

```cpp
template <typename T>
inline constexpr bool has_size_v = HasSize<T>::value;
```

### Пример 6: взаимоисключающие условия

```cpp
template <typename, typename = void>
struct HasLength : std::false_type {};

template <typename T>
struct HasLength<T, std::void_t<decltype(std::declval<const T&>().length())>>
    : std::true_type {};

template <typename T, std::enable_if_t<has_size_v<T>>* = nullptr>
auto get_count(const T& value) {
    return value.size();
}

template <typename T, std::enable_if_t<!has_size_v<T> && HasLength<T>::value>* = nullptr>
auto get_count(const T& value) {
    return value.length();
}
```

Если тип подходит под несколько SFINAE-перегрузок, будет неоднозначность.
Поэтому условия лучше делать взаимоисключающими.

## Подводные камни

SFINAE работает только в контексте подстановки шаблонных параметров.

```cpp
template <typename T>
void f() {
    typename T::type x; // ошибка уже внутри тела функции
}
```

Ошибки в теле функции не являются SFINAE.

SFINAE также работает при выборе частичной специализации шаблона класса или
переменной.

`enable_if` может сделать сигнатуру трудной для чтения.

```cpp
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
void f(T value);
```

Две функции, которые отличаются только значением по умолчанию у шаблонного
параметра, считаются одним и тем же шаблоном.

```cpp
template <typename T, typename = decltype(std::declval<T>().size())>
void f(const T&);

template <typename T, typename = decltype(std::declval<T>().length())>
void f(const T&); // ошибка: повторное объявление
```

Чтобы сделать разные перегрузки, условие часто помещают в тип нетипового
шаблонного параметра:

```cpp
template <typename T, decltype(std::declval<T>().size())* = nullptr>
void f(const T&);
```

В C++20 для новых интерфейсов чаще используют концепты.

SFINAE может давать сложные ошибки компиляции, особенно при цепочке шаблонов.

## Саммари

- SFINAE убирает неподходящую перегрузку без ошибки компиляции.
- SFINAE работает в непосредственном контексте, но не в теле функции.
- `std::enable_if_t` включает шаблон по условию.
- `std::declval` помогает писать проверки выражений внутри `decltype`.
- `std::void_t` удобен для проверки существования выражений.
- Условия у SFINAE-перегрузок лучше делать взаимоисключающими.
- SFINAE применяется и при выборе частичных специализаций.
- В C++20 концепты обычно читаются лучше.
