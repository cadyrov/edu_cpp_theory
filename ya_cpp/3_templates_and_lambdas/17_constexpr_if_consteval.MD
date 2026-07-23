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

`constexpr` не означает "всегда compile-time": функция может выполниться и в
runtime, если контекст не требует константного выражения.

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

### Пример 2: `constexpr` переменная

```cpp
constexpr int size = factorial(5);
int buffer[size]{};
```

`constexpr`-переменная обязана инициализироваться константным выражением.
`const` такой гарантии не дает.

### Пример 3: `constexpr` лямбда

```cpp
#include <cstddef>

auto hash = [](const char* str) constexpr {
    std::size_t value = 2166136261u;

    while (*str) {
        value ^= static_cast<unsigned char>(*str++);
        value *= 16777619u;
    }

    return value;
};

static_assert(hash("OK") != 0);
```

Лямбда может быть `constexpr` автоматически, если ее тело допустимо для
compile-time вычисления. Спецификатор `constexpr` можно написать явно.

### Пример 4: литеральный тип

```cpp
struct Point {
    int x;
    int y;

    constexpr Point(int x, int y) : x(x), y(y) {}
};

constexpr Point p{1, 2};
```

Для `constexpr`-объекта тип должен быть литеральным: его можно создать и
использовать во время вычисления константного выражения.

### Пример 5: `if constexpr`

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

### Пример 6: `if constexpr` и `requires`

```cpp
#include <cstddef>

template <typename Container>
auto get_count(const Container& value)
    requires(requires { value.size(); } || requires { value.length(); })
{
    if constexpr (requires { value.size(); }) {
        return value.size();
    } else {
        return value.length();
    }
}
```

Так можно заменить несколько SFINAE-перегрузок одной функцией.

### Пример 7: `dependent_false`

```cpp
template <typename>
inline constexpr bool dependent_false_v = false;

template <typename T>
void print_kind(const T& value) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "integer: " << value << '\n';
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "float: " << value << '\n';
    } else {
        static_assert(dependent_false_v<T>, "unsupported type");
    }
}
```

До C++23 простой `static_assert(false)` в отброшенной ветке обычно заменяли
зависимым выражением.

### Пример 8: `std::is_constant_evaluated`

```cpp
#include <type_traits>

constexpr int checked_div(int a, int b) {
    if (std::is_constant_evaluated() && b == 0) {
        return 0;
    }

    return a / b;
}
```

`std::is_constant_evaluated()` позволяет выбрать разный код для compile-time и
runtime. В C++23 для этого часто используют `if consteval`.

### Пример 9: `consteval`

```cpp
consteval int checked_square(int x) {
    return x * x;
}

constexpr int value = checked_square(7);
```

Вызов `checked_square` должен быть вычислен во время компиляции.

`consteval` можно использовать и у лямбды.

```cpp
auto hash_now = [](const char* text) consteval {
    return text[0];
};
```

### Пример 10: `if consteval`

```cpp
consteval int compile_time_only(int value) {
    return value;
}

int runtime_only(int value) {
    return value;
}

constexpr int maybe_compile_time(int value) {
    if consteval {
        return compile_time_only(value);
    } else {
        return runtime_only(value);
    }
}
```

`if consteval` нужен, когда из `constexpr`-функции нужно вызвать немедленную
функцию только в compile-time ветке.

### Пример 11: `constinit`

```cpp
constexpr int initial_value() {
    return 42;
}

constinit int global_value = initial_value();
```

`constinit` гарантирует статическую инициализацию глобальной или статической
переменной, но сама переменная не становится `const`.

### Пример 12: constexpr и стандартная библиотека

```cpp
#include <algorithm>
#include <array>

constexpr int median3(std::array<int, 3> values) {
    std::sort(values.begin(), values.end());
    return values[1];
}

static_assert(median3({3, 1, 2}) == 2);
```

В C++20 многие алгоритмы и типы стандартной библиотеки стали пригодны для
compile-time вычислений.

## Подводные камни

`constexpr` не гарантирует compile-time вычисление при каждом вызове.

```cpp
int x = 10;
int y = square(x); // может быть runtime
```

Для обязательного compile-time вызова используют `consteval`.

`constexpr`-функция должна иметь определение, доступное компилятору в точке
compile-time вызова. Поэтому такие функции часто размещают в заголовках;
`constexpr`-функция неявно `inline`.

`if constexpr` отбрасывает ветку только когда условие известно во время компиляции.

```cpp
if constexpr (std::is_integral_v<T>) {
}
```

Условие обычно зависит от шаблонного параметра.

Отброшенная ветка не инстанцируется, но синтаксически код все равно должен быть корректным.

Вне шаблона `if constexpr` не спасает от некорректного кода в ветке: обе ветки
должны быть компилируемы.

`consteval` нельзя вызвать с runtime-значением.

```cpp
int x = 5;
auto y = checked_square(x); // ошибка
```

`std::is_constant_evaluated()` не позволяет вызвать `consteval`-функцию с
параметром обычной `constexpr`-функции. Для этого в C++23 нужен `if consteval`.

`constinit` проверяет только инициализацию. После инициализации переменную можно
изменять, и ее нельзя использовать как `constexpr`-значение.

Во время compile-time вычислений компилятор диагностирует UB, например выход за
границы массива. Это удобно использовать в `static_assert`-тестах.

Указатель на объект, созданный в compile-time динамической памяти, нельзя
"вынести" в runtime-объект.

```cpp
constexpr int* bad() {
    return new int{1};
}

constexpr int* p = bad(); // ошибка
```

## Саммари

- `constexpr` разрешает compile-time вычисления.
- `constexpr` функция может выполняться и во время выполнения.
- `constexpr`-переменная требует константного выражения.
- `constexpr` применим к функциям, переменным, конструкторам, методам и лямбдам.
- Для `constexpr`-объекта нужен литеральный тип.
- `if constexpr` выбирает ветку на этапе компиляции.
- Отброшенная ветка `if constexpr` не инстанцируется.
- `if constexpr` удобно сочетать с `requires`-выражениями.
- `std::is_constant_evaluated` и `if consteval` помогают различать compile-time и runtime.
- `consteval` требует немедленного compile-time вычисления.
- `constinit` гарантирует статическую инициализацию, но не делает переменную константой.
