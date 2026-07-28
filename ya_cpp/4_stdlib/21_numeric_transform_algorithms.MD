# 21. Численные и трансформирующие алгоритмы

## Суть

Эти алгоритмы заполняют диапазоны, меняют значения и считают накопленные результаты.

Основные группы:

- заполнение: `fill`, `iota`, `generate`, `generate_n`, `sample`;
- замена и преобразование: `replace`, `replace_if`, `transform`;
- накопление: `partial_sum`, `inclusive_scan`, `exclusive_scan`;
- метрики: `accumulate`, `reduce`, `transform_reduce`.

## Заполнение диапазона

```cpp
#include <algorithm>
#include <numeric>
#include <vector>

std::vector<int> values(5);

std::fill(values.begin(), values.end(), 42);
std::iota(values.begin(), values.end(), 1);
```

`std::fill` записывает одно значение. `std::iota` заполняет последовательными значениями.

```cpp
std::generate(values.begin(), values.end(), [n = 0]() mutable {
    return n += 2;
});
```

`std::generate` вызывает генератор для каждого элемента. `mutable` нужен, если лямбда меняет захваченное по значению состояние.

## generate_n и back_inserter

```cpp
#include <iterator>
#include <utility>

std::vector<int> fib;
fib.reserve(10);

std::generate_n(std::back_inserter(fib), 10, [prev = 0, cur = 1]() mutable {
    int next = prev + cur;
    return prev = std::exchange(cur, next);
});
```

Алгоритмы с суффиксом `_n` принимают начало и количество элементов. С `std::back_inserter` они добавляют элементы через `push_back`.

Если размер известен заранее, вызывай `reserve`.

## sample

```cpp
#include <random>

std::vector<std::string> players{"Igor", "Vlad", "Roman", "Oleg"};
std::vector<std::string> out;

std::sample(
    players.begin(), players.end(),
    std::back_inserter(out),
    2,
    std::mt19937{std::random_device{}()}
);
```

`std::sample` выбирает случайные элементы из диапазона. Каждый элемент имеет равный шанс попасть в выборку.

## replace и transform

```cpp
std::vector<int> values{1, 2, 3, 2, 4};

std::replace(values.begin(), values.end(), 2, 42);
std::replace_if(values.begin(), values.end(), [](int x) {
    return x % 2 == 0;
}, 0);
```

`replace` заменяет значение, `replace_if` заменяет по условию.

```cpp
std::vector<int> squared;
squared.reserve(values.size());

std::transform(values.begin(), values.end(), std::back_inserter(squared), [](int x) {
    return x * x;
});
```

`std::transform` применяет функцию к каждому элементу и пишет результат в выходной диапазон.

Есть версия для двух диапазонов:

```cpp
std::vector<double> vals{10.0, 15.5};
std::vector<double> weights{0.9, 1.1};
std::vector<double> result(vals.size());

std::transform(vals.begin(), vals.end(), weights.begin(), result.begin(), std::multiplies<double>{});
```

## Частичные суммы и scan

```cpp
#include <numeric>

std::vector<int> values{1, 2, 3, 4};
std::vector<int> sums(values.size());

std::partial_sum(values.begin(), values.end(), sums.begin());
// 1 3 6 10
```

`partial_sum` идет строго слева направо.

```cpp
std::inclusive_scan(values.begin(), values.end(), sums.begin());
```

`inclusive_scan` похож на `partial_sum`, но может не гарантировать строгий порядок операций и поддерживает начальное значение.

```cpp
std::vector<int> starts(values.size());

std::exclusive_scan(values.begin(), values.end(), starts.begin(), 0);
```

`exclusive_scan` считает накопление до текущего элемента, исключая сам текущий элемент.

## transform_inclusive_scan

```cpp
std::vector<int> values{1, 2, 3};
std::vector<int> result(values.size());

std::transform_inclusive_scan(
    values.begin(), values.end(),
    result.begin(),
    std::plus<int>{},
    [](int x) { return x * x; }
);
// 1 5 14
```

Алгоритм сначала преобразует элемент, затем накапливает результат. Это позволяет сделать два действия за один проход.

## accumulate, reduce, transform_reduce

```cpp
std::vector<int> income{7300, 2400, 500};

int sum = std::accumulate(income.begin(), income.end(), 0);
```

`std::accumulate` последовательно накапливает значение слева направо.

```cpp
int fastSum = std::reduce(income.begin(), income.end(), 0);
```

`std::reduce` может менять порядок вычислений, поэтому операция должна быть ассоциативной и коммутативной.

```cpp
std::vector<int> values{1, 2, 3};

int sumOfSquares = std::transform_reduce(
    values.begin(), values.end(),
    0,
    std::plus<int>{},
    [](int x) { return x * x; }
);
```

`transform_reduce` сначала преобразует элементы, затем сворачивает их в одно значение.

Для двух диапазонов это удобно для скалярного произведения:

```cpp
std::vector<int> a{1, 2, 3};
std::vector<int> b{10, 20, 30};

int dot = std::transform_reduce(a.begin(), a.end(), b.begin(), 0);
```

## Подводные камни

## 1. Начальное значение задает тип

```cpp
std::vector<double> values{1.5, 2.5};
auto sum = std::accumulate(values.begin(), values.end(), 0);
```

Здесь накопление идет как `int`. Нужно `0.0`.

## 2. Для результата нужно место

```cpp
std::vector<int> out;
std::transform(values.begin(), values.end(), out.begin(), f); // ошибка
```

Используй `resize` или `std::back_inserter`.

## 3. `back_inserter` без `reserve` может быть медленнее

Если заранее знаешь количество элементов, выдели память через `reserve`.

## 4. `reduce` не равен `accumulate`

`accumulate` гарантирует порядок слева направо. `reduce` может менять порядок ради скорости.

## 5. `scan` отличается от `partial_sum`

`partial_sum` строгий и последовательный. `inclusive_scan` и `exclusive_scan` удобнее для начального значения и потенциального параллелизма.

## Саммари

- `fill`, `iota`, `generate`, `generate_n` заполняют диапазоны.
- `sample` выбирает случайные элементы из диапазона.
- `replace` и `replace_if` заменяют значения.
- `transform` преобразует один или два диапазона.
- `partial_sum`, `inclusive_scan`, `exclusive_scan` считают накопленные значения.
- `transform_inclusive_scan` совмещает преобразование и накопление.
- `accumulate` накапливает строго слева направо.
- `reduce` может быть быстрее, но порядок операций не гарантирован.
- `transform_reduce` совмещает преобразование и свертку.
