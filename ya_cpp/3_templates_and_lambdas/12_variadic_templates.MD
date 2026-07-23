# 12. Вариабельные шаблоны и их идиомы

## Суть

Вариабельный шаблон принимает произвольное количество параметров.

```cpp
template <typename... Args>
void log(Args... args) {
}
```

`Args...` - пакет типов, `args...` - пакет значений.

## Примеры

### Пример 1: количество аргументов

```cpp
template <typename... Args>
constexpr std::size_t count_args(Args... args) {
    return sizeof...(Args);
}

int main() {
    static_assert(count_args(1, 2.0, "x") == 3);
}
```

### Пример 2: раскрытие пакета

```cpp
#include <iostream>

template <typename... Args>
void print_all(Args... args) {
    ((std::cout << args << ' '), ...);
}
```

Это fold expression.

### Разновидности fold expressions

Fold expression сворачивает пакет с помощью бинарного оператора.

```cpp
(pack op ...)        // унарная правая: E1 op (... op En)
(... op pack)        // унарная левая:  (... op E2) op En
(pack op ... op init) // бинарная правая: E1 op (... op (En op init))
(init op ... op pack) // бинарная левая:  ((init op E1) op ...) op En
```

`pack` - выражение с нераскрытым пакетом, `op` - бинарный оператор,
`init` - начальное значение, не зависящее от пакета.

Правый и левый fold отличаются расстановкой скобок. Для ассоциативных операций,
например `+`, это обычно неважно. Для неассоциативных, например `-`, результат
может отличаться.

```cpp
template <typename... Args>
auto right_subtract(Args... args) {
    return (args - ...);       // a - (b - c)
}

template <typename... Args>
auto left_subtract(Args... args) {
    return (... - args);       // (a - b) - c
}

static_assert(right_subtract(8, 2, 2) == 8);
static_assert(left_subtract(8, 2, 2) == 4);
```

Бинарная свертка удобна, когда нужен `init` или нужно поддержать пустой пакет.

```cpp
template <typename... Args>
auto sum(Args... args) {
    return (args + ... + 0);   // 0 для пустого пакета
}

template <typename... Args>
void println(Args... args) {
    (std::cout << ... << args) << '\n';
}
```

### Оператор `,` и fold expression

Оператор `,` удобен, когда нужно не агрегировать значения, а выполнить действие
для каждого аргумента пакета.

```cpp
#include <iostream>

void print_one_with_space(const auto& value) {
    std::cout << value << ' ';
}

template <typename... Args>
void print_with_space(Args&&... args) {
    (print_one_with_space(args), ..., (std::cout << '\n'));
}

int main() {
    print_with_space(3.14, 42, "myau"); // 3.14 42 myau
}
```

Это бинарная правая свертка по оператору `,`.
Для `,` порядок вычисления всегда слева направо, поэтому здесь нет практической
разницы между правой и левой сверткой.

### Короткосхемные вычисления

Fold expression с `&&` и `||` сохраняет короткосхемность: вычисление
останавливается, когда результат уже известен.

```cpp
#include <iostream>

bool print_arg(bool value) {
    std::cout << std::boolalpha << value << '\n';
    return value;
}

template <typename... Args>
auto check_short_circuit(Args... args) {
    return (print_arg(args) || ...);
}

int main() {
    check_short_circuit(false, true, false, true);
    // false
    // true
}
```

`||` прекращает вычисления на первом `true`, а `&&` - на первом `false`.

### Пример 3: идеальная передача пакета

```cpp
#include <utility>

template <typename T, typename... Args>
T make(Args&&... args) {
    return T(std::forward<Args>(args)...);
}
```

Каждый аргумент передается дальше со своей категорией значения.

### Пример 4: рекурсия по пакету значений

```cpp
template <auto First, auto... Rest>
struct MaxValue {
private:
    static const auto rest_max = MaxValue<Rest...>::value;

public:
    static const auto value = (First > rest_max) ? First : rest_max;
};

template <auto Val>
struct MaxValue<Val> {
    static const auto value = Val;
};

template <auto... Values>
inline const auto max_value = MaxValue<Values...>::value;

static_assert(max_value<1, 5, 3, 9, 2> == 9);
static_assert(max_value<-5, -1, -10> == -1);
static_assert(max_value<'a', 'z', 'x'> == 'z');
```

`auto... Values` - пакет нетиповых параметров шаблона.
Частичная специализация `MaxValue<Val>` останавливает рекурсию.

## Подводные камни

Пакет нужно раскрывать через `...`.

```cpp
args;  // ошибка
args...; // раскрытие
```

Пустой пакет должен быть учтен.

```cpp
print_all(); // должно компилироваться?
```

Fold expression для пустого пакета работает не для всех операций.

Порядок вычисления важен.

```cpp
((std::cout << args << '\n'), ...);
```

Здесь используется оператор `,`, он задает порядок слева направо.

Не забывай `std::forward<Args>(args)...`, если нужна идеальная передача.

```cpp
target(args...); // может потерять rvalue
target(std::forward<Args>(args)...);
```

## Саммари

- `typename... Args` задает пакет типов.
- `Args...` и `args...` раскрывают пакет.
- `sizeof...(Args)` дает размер пакета.
- Fold expressions упрощают обработку пакета.
- Для передачи дальше используй `std::forward<Args>(args)...`.
- Нужно отдельно думать о пустом пакете.
