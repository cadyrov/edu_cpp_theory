# 1. Шаблоны функций

## Суть

Шаблон функции описывает не одну функцию, а правило для создания функций.

```cpp
template <typename T>
T max_value(T a, T b) {
    return a < b ? b : a;
}
```

Компилятор сам создает нужную версию функции по типам аргументов.

```cpp
max_value(1, 2);       // T = int
max_value(1.5, 2.5);   // T = double
```

## Примеры

### Пример 1: один тип

```cpp
template <typename T>
T square(T x) {
    return x * x;
}

int main() {
    int a = square(5);
    double b = square(1.5);
}
```

### Пример 2: несколько типов

```cpp
template <typename T, typename U>
auto add(T a, U b) {
    return a + b;
}

int main() {
    auto x = add(1, 2.5); // double
}
```

### Пример 3: явное указание типа

```cpp
template <typename T>
T make_zero() {
    return T{};
}

int main() {
    auto x = make_zero<int>();
}
```

## Подводные камни

Шаблон должен быть виден в месте использования. Поэтому шаблоны обычно пишут в `.hpp`.

```cpp
// foo.hpp
template <typename T>
T foo(T x) {
    return x;
}
```

Типы аргументов должны подходить под тело шаблона.

```cpp
template <typename T>
T twice(T x) {
    return x + x;
}
```

Если для `T` нет `operator+`, код не скомпилируется.

Вывод типа не делает неявное приведение между разными `T`.

```cpp
max_value(1, 2.5); // ошибка: T не может быть и int, и double
```

Можно указать тип явно:

```cpp
max_value<double>(1, 2.5);
```

## Саммари

- Шаблон функции создает функции для разных типов.
- `typename` и `class` в параметрах шаблона почти одно и то же.
- Тип часто выводится из аргументов.
- Если тип нельзя вывести, его указывают явно.
- Шаблоны обычно размещают в заголовочных файлах.
- Ошибки в шаблоне часто появляются только при конкретном использовании.
