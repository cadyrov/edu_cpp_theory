# 6. Шаблонные параметры: вещественные числа, пользовательские типы

## Суть

В C++20 нетиповые параметры шаблона стали шире.

Можно использовать не только целые числа, но и некоторые пользовательские типы.

```cpp
struct Point {
    int x;
    int y;
};

template <Point P>
struct Marker {};
```

Вещественные параметры поддерживаются не всеми компиляторами одинаково, поэтому с ними нужно быть осторожным.

## Примеры

### Пример 1: пользовательский тип

```cpp
struct Size {
    int width;
    int height;
};

template <Size S>
struct Image {
    static constexpr int width = S.width;
    static constexpr int height = S.height;
};

int main() {
    using Icon = Image<Size{32, 32}>;
}
```

### Пример 2: строка через пользовательский тип

```cpp
template <std::size_t N>
struct FixedString {
    char value[N];

    constexpr FixedString(const char (&str)[N]) {
        for (std::size_t i = 0; i < N; ++i) {
            value[i] = str[i];
        }
    }
};

template <FixedString Name>
struct Field {};

using Id = Field<"id">;
```

### Пример 3: вещественное число

```cpp
template <double Value>
struct Constant {
    static constexpr double value = Value;
};
```

Такой код требует поддержки компилятора и стандарта.

### Пример 4: epsilon как параметр шаблона

Если точность сравнения не должна меняться от вызова к вызову, `epsilon` можно сделать нетиповым параметром шаблона.

```cpp
#include <cmath>
#include <iostream>

template <typename T, T epsilon = static_cast<T>(0.00001)>
bool is_equal(T a, T b) {
    return std::abs(a - b) < epsilon;
}

int main() {
    std::cout << is_equal(1.000001, 1.000002) << '\n';
    std::cout << is_equal<float, 0.0001f>(1.0001f, 1.0003f) << '\n';
}
```

Вывод:

```text
1
0
```

Здесь `T` - типовой параметр, а `epsilon` - нетиповой параметр типа `T`.

Тип `epsilon` не фиксирован заранее. Когда компилятор выводит или получает `T`, `epsilon` становится значением этого типа.

```cpp
is_equal(1.0, 1.000001); // T = double, epsilon = double
is_equal<float, 0.0001f>(1.0001f, 1.0003f); // T = float, epsilon = float
```

У `epsilon` есть значение по умолчанию.

Если нужно явно указать `epsilon`, придется явно указать и все параметры перед ним:

```cpp
is_equal<float, 0.0001f>(1.0001f, 1.0003f);
```

Так нельзя:

```cpp
is_equal<0.0001f>(1.0001f, 1.0003f); // ошибка
```

Первый шаблонный параметр - `T`, поэтому компилятор будет пытаться прочитать `0.0001f` как тип.

## Подводные камни

Пользовательский тип должен быть пригоден для шаблонного параметра.

Обычно это простой literal type:

```cpp
struct Config {
    int value;
};
```

Тип с приватными полями или сложной логикой может не подойти.

```cpp
class Config {
    int value;
};
```

Вещественные значения опасны из-за точности.

```cpp
Constant<0.1>;
```

`0.1` нельзя точно представить в binary floating point.

Похожие выражения с вещественными числами могут дать разные значения и разные типы.

```cpp
Constant<0.3>;
Constant<0.1 + 0.2>; // может быть другой тип
```

Разные значения создают разные типы.

```cpp
Image<Size{32, 32}>;
Image<Size{64, 64}>; // другой тип
```

## Саммари

- В C++20 нетиповые параметры стали мощнее.
- Можно передавать простые пользовательские типы.
- Это удобно для compile-time конфигурации.
- Строки часто передают через `FixedString`.
- Вещественный параметр может зависеть от типа: `template <typename T, T value>`.
- У нетиповых параметров могут быть значения по умолчанию.
- С вещественными параметрами нужна осторожность.
- Разные значения по-прежнему создают разные типы.
