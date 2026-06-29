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
- С вещественными параметрами нужна осторожность.
- Разные значения по-прежнему создают разные типы.

