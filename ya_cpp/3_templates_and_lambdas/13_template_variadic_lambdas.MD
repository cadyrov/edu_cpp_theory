# 13. Шаблонные и вариабельные лямбда-выражения, идиомы с лямбдами

## Суть

Лямбда может быть обобщенной.

```cpp
auto print = [](const auto& x) {
    std::cout << x << '\n';
};
```

В C++20 у лямбды можно явно указать шаблонные параметры.

```cpp
auto same = []<typename T>(T a, T b) {
    return a == b;
};
```

Лямбда также может принимать пакет аргументов.

## Примеры

### Пример 1: generic lambda

```cpp
auto add = [](auto a, auto b) {
    return a + b;
};

auto x = add(1, 2);
auto y = add(1.5, 2.5);
```

### Пример 2: шаблонная лямбда

```cpp
auto cast_to = []<typename T>(auto value) {
    return static_cast<T>(value);
};

int x = cast_to.operator()<int>(1.5);
```

### Пример 3: вариабельная лямбда

```cpp
#include <iostream>

auto print_all = [](const auto&... args) {
    ((std::cout << args << ' '), ...);
};

print_all(1, "hello", 2.5);
```

### Пример 4: overloaded

```cpp
template <typename... Ts>
struct Overloaded : Ts... {
    using Ts::operator()...;
};

template <typename... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;
```

Так можно объединять несколько лямбд в один объект.

## Подводные камни

`auto` в параметре лямбды делает `operator()` шаблонным.

```cpp
auto f = [](auto x) {};
```

Это уже не одна функция для одного типа, а шаблон вызова.

Явный вызов шаблонной лямбды выглядит непривычно.

```cpp
f.operator()<int>(10);
```

Fold expression должен корректно работать с пустым пакетом.

```cpp
auto print_all = [](const auto&... args) {
    ((std::cout << args), ...);
};
```

Для пустого пакета это допустимо с оператором `,`, но не со всеми операциями.

Обобщенные лямбды могут давать длинные ошибки компиляции.

## Саммари

- `auto` в параметрах делает лямбду обобщенной.
- В C++20 можно писать явные шаблонные параметры лямбды.
- `auto... args` задает вариабельную лямбду.
- Fold expressions удобно раскрывают пакет.
- Идиома `Overloaded` объединяет несколько лямбд.
- Чем обобщеннее лямбда, тем важнее понятные ограничения и простое тело.
