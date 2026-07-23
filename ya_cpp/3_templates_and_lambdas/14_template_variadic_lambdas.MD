# 14. Шаблонные и вариабельные лямбда-выражения, идиомы с лямбдами

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

```cpp
auto count = []<typename... Ts>(Ts&&... args) {
    return sizeof...(Ts);
};
```

То есть шаблонная лямбда тоже может быть вариабельной.

## Примеры

### Пример 1: generic lambda

```cpp
auto add = [](auto a, auto b) {
    return a + b;
};

auto x = add(1, 2);
auto y = add(1.5, 2.5);
```

У generic lambda компилятор создает обычный класс с шаблонным `operator()`.

### Пример 2: лямбда как локальная функция

```cpp
#include <iostream>
#include <string_view>

void parse_line(std::string_view line) {
    std::size_t line_number = 1;

    auto report_error = [&](std::string_view message) {
        std::cerr << "line " << line_number << ": " << message << '\n';
    };

    if (line.empty()) {
        report_error("empty line");
    }
}
```

Лямбда может заменить небольшую локальную функцию, если ей нужен доступ к
локальному контексту.

### Пример 3: IIFE

```cpp
#include <cstdlib>
#include <functional>
#include <string>

const std::string config = [] {
    if (const char* value = std::getenv("APP_CONFIG")) {
        return std::string{value};
    }

    return std::string{"default"};
}();

const auto other_config = std::invoke([] {
    return std::string{"default"};
});
```

IIFE сразу вызывает лямбду и удобна для сложной инициализации `const`-объекта.

### Пример 4: шаблонная лямбда

```cpp
auto cast_to = []<typename T>(auto value) {
    return static_cast<T>(value);
};

int x = cast_to.operator()<int>(1.5);
```

Явные шаблонные параметры нужны, когда имя типа нужно использовать в теле или
в сигнатуре лямбды.

### Пример 5: perfect forwarding

```cpp
#include <utility>

auto forward_to = []<typename F, typename T>(F&& f, T&& value) -> decltype(auto) {
    return std::forward<F>(f)(std::forward<T>(value));
};

auto short_form = [](auto&& f, auto&& value) -> decltype(auto) {
    return std::forward<decltype(f)>(f)(
        std::forward<decltype(value)>(value)
    );
};
```

В форме с `auto&&` тип берут через `decltype(value)`.

### Пример 6: вариабельная лямбда

```cpp
#include <iostream>

auto print_all = [](const auto&... args) {
    ((std::cout << args << ' '), ...);
};

print_all(1, "hello", 2.5);
```

### Пример 7: захват пакета

```cpp
#include <iostream>

template <typename... Args>
auto make_printer(Args... args) {
    return [args...] {
        ((std::cout << args << ' '), ...);
    };
}

auto printer = make_printer(1, "hello", 2.5);
printer();
```

`[args...]` захватывает каждый элемент пакета по значению.
Для ссылочного захвата можно написать `[&args...]`.

### Пример 8: `std::bind_front` и `std::bind_back`

`std::bind_front` и `std::bind_back` создают вызываемый объект с заранее
зафиксированными аргументами.

```cpp
#include <functional>
#include <iostream>
#include <string_view>

void log_value(std::string_view name, int value) {
    std::cout << name << ": " << value << '\n';
}

auto log_temperature = std::bind_front(log_value, "temperature");
log_temperature(23); // log_value("temperature", 23)
```

`bind_front` фиксирует аргументы слева, `bind_back` - справа.
`std::bind_front` появился в C++20, `std::bind_back` - в C++23.

```cpp
#include <algorithm>
#include <functional>
#include <vector>

std::vector values{8, 12, 5, 15, 3};

auto count = std::count_if(
    values.begin(),
    values.end(),
    std::bind_back(std::greater<>{}, 10)
); // 2
```

Функциональный объект - это функция, указатель на функцию или объект с
`operator()`. Вызываемый объект шире: это все, что можно вызвать через
`std::invoke`, включая указатели на методы и поля.

### Пример 9: захват пакета функций

```cpp
#include <functional>
#include <utility>

template <typename... Funcs>
auto make_call_each(Funcs&&... funcs) {
    return [...funcs = std::forward<Funcs>(funcs)](auto&&... args) {
        (std::invoke(funcs, std::forward<decltype(args)>(args)...), ...);
    };
}
```

Такая лямбда хранит набор функций и вызывает каждую с переданным пакетом
аргументов. Инициализирующий захват `...funcs = ...` позволяет переносить
move-only функциональные объекты.

### Пример 10: overloaded

```cpp
template <typename... Ts>
struct Overloaded : Ts... {
    using Ts::operator()...;
};

template <typename... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;
```

Так можно объединять несколько лямбд в один объект.

### Пример 11: `std::apply` и tuple

```cpp
#include <tuple>
#include <utility>

template <typename Visitor, typename Tuple>
void visit_tuple(Visitor&& visitor, Tuple&& tuple) {
    std::apply(
        [&visitor](auto&&... args) {
            (visitor(std::forward<decltype(args)>(args)), ...);
        },
        std::forward<Tuple>(tuple)
    );
}
```

`std::apply` раскрывает `tuple` в аргументы вызываемого объекта.

### Пример 12: рекурсивная лямбда

```cpp
auto fib_impl = [](auto& self, int n) -> int {
    return n <= 1 ? n : self(self, n - 1) + self(self, n - 2);
};

auto fib = [fib_impl](int n) {
    return fib_impl(fib_impl, n);
};
```

В C++23 можно короче через явный параметр `this`.

```cpp
auto fib = [](this auto& self, int n) -> int {
    return n <= 1 ? n : self(n - 1) + self(n - 2);
};
```

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

Не делай локальную лямбду слишком большой. Если она начинает хранить много
состояния и решать отдельную задачу, часто лучше вынести класс или функцию.

Рекурсию через `std::function` писать можно, но это обычно дороже, чем вариант
с `self` или явным параметром `this`.

## Саммари

- `auto` в параметрах делает лямбду обобщенной.
- Лямбда может быть локальной функцией с доступом к локальному контексту.
- IIFE помогает инициализировать `const`-объект сложным кодом.
- В C++20 можно писать явные шаблонные параметры лямбды.
- `auto... args` задает вариабельную лямбду.
- Шаблонная лямбда может принимать `typename... Ts`.
- Лямбда может захватить пакет через `[args...]` или `[&args...]`.
- Для perfect forwarding в generic lambda используй `std::forward<decltype(arg)>(arg)`.
- Инициализирующий захват пакета позволяет хранить move-only объекты.
- `std::bind_front` и `std::bind_back` фиксируют часть аргументов вызываемого объекта.
- Fold expressions удобно раскрывают пакет.
- Идиома `Overloaded` объединяет несколько лямбд.
- `std::apply` раскрывает `tuple` в аргументы callable-объекта.
- Рекурсивную лямбду можно написать через `self`, а в C++23 - через `this auto`.
- Чем обобщеннее лямбда, тем важнее понятные ограничения и простое тело.
