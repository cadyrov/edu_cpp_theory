# 3. Шаблон класса и переменной

## Суть

Шаблон класса описывает семейство типов.

```cpp
template <typename T>
struct Box {
    T value;
};
```

`Box<int>` и `Box<double>` - разные типы.

Шаблон переменной описывает семейство переменных.

```cpp
template <typename T>
constexpr T pi = T(3.1415926535);
```

## Примеры

### Пример 1: шаблон класса

```cpp
template <typename T>
struct Box {
    T value;
};

int main() {
    Box<int> a{10};
    Box<double> b{1.5};
}
```

### Пример 2: методы шаблонного класса

```cpp
template <typename T>
class Holder {
public:
    explicit Holder(T value)
        : value_(value) {}

    const T& get() const {
        return value_;
    }

private:
    T value_;
};
```

### Пример 3: шаблон переменной

```cpp
template <typename T>
constexpr T zero = T{};

int main() {
    int a = zero<int>;
    double b = zero<double>;
}
```

## Подводные камни

`Box<int>` и `Box<double>` не связаны наследованием.

```cpp
Box<int> a{1};
Box<double> b = a; // ошибка
```

Параметр шаблона класса обычно нужно указать.

```cpp
Box<int> x{10};
```

В C++17 появился CTAD: вывод аргументов шаблона класса.

```cpp
Box x{10}; // T = int
```

Но CTAD работает не всегда очевидно, особенно со сложными конструкторами.

Статические поля шаблонного класса существуют отдельно для каждого `T`.

```cpp
Counter<int>::value;
Counter<double>::value; // другая переменная
```

## Саммари

- Шаблон класса создает разные типы для разных параметров.
- `Box<int>` и `Box<double>` - разные независимые типы.
- Методы шаблонного класса зависят от параметров шаблона.
- Шаблон переменной создает переменную для каждого набора параметров.
- CTAD может вывести параметры класса, но не стоит полагаться на него в сложном коде.

