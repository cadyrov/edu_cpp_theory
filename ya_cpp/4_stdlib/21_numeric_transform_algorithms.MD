# 21. Численные и трансформирующие алгоритмы

## Суть

Численные алгоритмы считают агрегаты.

Трансформирующие алгоритмы создают или меняют значения на основе диапазона.

Частые алгоритмы:

- `std::accumulate`;
- `std::reduce`;
- `std::transform`;
- `std::partial_sum`;
- `std::iota`.

## Пример 1: accumulate

```cpp
#include <numeric>
#include <vector>

std::vector<int> values{1, 2, 3, 4};

int sum = std::accumulate(values.begin(), values.end(), 0);
```

`sum` будет равен `10`.

## Пример 2: transform

```cpp
#include <algorithm>
#include <vector>

std::vector<int> values{1, 2, 3};
std::vector<int> result(values.size());

std::transform(values.begin(), values.end(), result.begin(), [](int x) {
    return x * 10;
});
```

`result` будет: `10 20 30`.

## Пример 3: iota

```cpp
#include <numeric>
#include <vector>

std::vector<int> values(5);

std::iota(values.begin(), values.end(), 1);
```

`values` будет: `1 2 3 4 5`.

## Пример 4: partial_sum

```cpp
std::vector<int> values{1, 2, 3};
std::vector<int> sums(values.size());

std::partial_sum(values.begin(), values.end(), sums.begin());
```

`sums` будет: `1 3 6`.

## Подводные камни

## 1. Начальное значение задает тип

```cpp
std::vector<double> values{1.5, 2.5};

auto sum = std::accumulate(values.begin(), values.end(), 0);
```

Здесь сумма будет считаться как `int`.

Нужно:

```cpp
auto sum = std::accumulate(values.begin(), values.end(), 0.0);
```

## 2. transform требует место для результата

```cpp
std::vector<int> result;

std::transform(values.begin(), values.end(), result.begin(), f); // ошибка
```

`result.begin()` не указывает на готовые элементы.

Используй `resize` или `std::back_inserter`.

## 3. reduce может менять порядок вычислений

```cpp
auto sum = std::reduce(values.begin(), values.end());
```

`reduce` допускает другой порядок операций.

Для чисел с плавающей точкой результат может немного отличаться.

## 4. accumulate идет слева направо

`std::accumulate` выполняет последовательное накопление.

Если важен порядок, он предсказуемее `std::reduce`.

## Саммари

- `accumulate` накапливает значение слева направо.
- Начальное значение влияет на тип результата.
- `transform` применяет функцию к элементам.
- Для `transform` нужно подготовить место результата или использовать `back_inserter`.
- `iota` заполняет последовательными значениями.
- `reduce` может менять порядок вычислений.
