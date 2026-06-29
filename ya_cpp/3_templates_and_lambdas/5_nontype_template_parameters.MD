# 5. Шаблонные параметры, не являющиеся типами

## Суть

Параметр шаблона может быть не типом, а значением.

```cpp
template <typename T, std::size_t N>
struct Array {
    T data[N];
};
```

`Array<int, 3>` и `Array<int, 5>` - разные типы.

## Примеры

### Пример 1: размер массива

```cpp
#include <cstddef>

template <typename T, std::size_t N>
struct StaticArray {
    T data[N];

    std::size_t size() const {
        return N;
    }
};

int main() {
    StaticArray<int, 4> a{};
}
```

### Пример 2: значение как параметр

```cpp
template <int Limit>
bool in_range(int x) {
    return x >= 0 && x < Limit;
}

int main() {
    bool ok = in_range<10>(7);
}
```

### Пример 3: ссылка на объект

```cpp
extern const int default_value;

template <const int& Value>
int get() {
    return Value;
}
```

## Подводные камни

Значение должно быть известно на этапе компиляции.

```cpp
int n = 10;
StaticArray<int, n> a; // ошибка
```

Нужно использовать константное выражение.

```cpp
constexpr int n = 10;
StaticArray<int, n> a;
```

Разные значения создают разные типы.

```cpp
StaticArray<int, 3> a;
StaticArray<int, 4> b;

a = b; // ошибка
```

Большое количество разных значений может увеличить время компиляции и размер кода.

Нетиповые параметры удобны, но они переносят часть данных в тип.

## Саммари

- Нетиповой параметр шаблона - это значение, а не тип.
- Значение должно быть известно во время компиляции.
- Частый пример - размер статического массива.
- Разные значения обычно создают разные типы.
- Это удобно для проверок и оптимизаций на этапе компиляции.
- Цена - больше разных инстанцирований шаблона.
