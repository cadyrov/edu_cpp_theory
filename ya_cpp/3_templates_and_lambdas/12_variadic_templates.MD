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

### Пример 3: идеальная передача пакета

```cpp
#include <utility>

template <typename T, typename... Args>
T make(Args&&... args) {
    return T(std::forward<Args>(args)...);
}
```

Каждый аргумент передается дальше со своей категорией значения.

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
