# 4. Специализация шаблона

## Суть

Специализация позволяет задать отдельную реализацию шаблона для конкретного типа.

```cpp
template <typename T>
struct TypeName {
    static constexpr const char* value = "unknown";
};

template <>
struct TypeName<int> {
    static constexpr const char* value = "int";
};
```

Общий шаблон работает по умолчанию, специализация - для выбранного случая.

## Примеры

### Пример 1: полная специализация

```cpp
template <typename T>
struct IsPointer {
    static constexpr bool value = false;
};

template <typename T>
struct IsPointer<T*> {
    static constexpr bool value = true;
};

int main() {
    static_assert(!IsPointer<int>::value);
    static_assert(IsPointer<int*>::value);
}
```

Здесь `T*` - частичная специализация.

### Пример 2: полная специализация функции

```cpp
template <typename T>
void print(T value) {
    std::cout << value << '\n';
}

template <>
void print<bool>(bool value) {
    std::cout << (value ? "true" : "false") << '\n';
}
```

### Пример 3: проще через перегрузку

```cpp
template <typename T>
void print(T value) {
    std::cout << value << '\n';
}

void print(bool value) {
    std::cout << (value ? "true" : "false") << '\n';
}
```

Для функций перегрузка часто проще специализации.

## Подводные камни

Частичная специализация функций запрещена.

```cpp
template <typename T>
void foo(T* p) {} // это перегрузка, не частичная специализация
```

Специализацию нужно объявлять в той же области имен, что и основной шаблон.

```cpp
namespace lib {
    template <typename T>
    struct X {};

    template <>
    struct X<int> {};
}
```

Слишком много специализаций быстро усложняют код.

Иногда лучше использовать `if constexpr`.

```cpp
template <typename T>
void print(T value) {
    if constexpr (std::is_same_v<T, bool>) {
        std::cout << (value ? "true" : "false") << '\n';
    } else {
        std::cout << value << '\n';
    }
}
```

## Саммари

- Специализация меняет поведение шаблона для конкретных типов.
- Полная специализация задает точный набор параметров.
- Частичная специализация задает шаблонный частный случай.
- Классы можно частично специализировать, функции - нет.
- Для функций чаще используют перегрузку.
- Для простых ветвлений по типу подходит `if constexpr`.

