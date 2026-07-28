# 18. Концепция no raw loops

## Суть

No raw loops — идея не писать ручной цикл там, где есть готовый алгоритм стандартной библиотеки.

Алгоритм показывает намерение: поиск, проверка, подсчет, сравнение или поиск подпоследовательности.

```cpp
auto it = std::find(values.begin(), values.end(), 42);
```

Такой код обычно проще читать, чем цикл с индексами, флагами и `break`.

## Поиск элемента

```cpp
#include <algorithm>
#include <vector>

std::vector<int> values{1, 2, 3, 4, 5};

auto it = std::find(values.begin(), values.end(), 3);
auto even = std::find_if(values.begin(), values.end(), [](int x) {
    return x % 2 == 0;
});
auto odd = std::find_if_not(values.begin(), values.end(), [](int x) {
    return x % 2 == 0;
});
```

`std::find` ищет значение, `std::find_if` — первый элемент по условию, `std::find_if_not` — первый элемент, который условию не подходит.

Сложность в худшем случае — `O(N)`.

## Проверка условия

```cpp
bool allPositive = std::all_of(values.begin(), values.end(), [](int x) {
    return x > 0;
});

bool hasNegative = std::any_of(values.begin(), values.end(), [](int x) {
    return x < 0;
});

bool noZeroes = std::none_of(values.begin(), values.end(), [](int x) {
    return x == 0;
});
```

Используй:

- `all_of`, если условие должно выполняться для всех;
- `any_of`, если достаточно одного подходящего элемента;
- `none_of`, если подходящих элементов быть не должно.

## Поиск повторов и подпоследовательностей

```cpp
std::vector<int> values{1, 2, 3, 3, 4};

auto duplicate = std::adjacent_find(values.begin(), values.end());
```

`std::adjacent_find` ищет первую пару соседних элементов, подходящих под сравнение.

```cpp
std::vector<int> temperatures{22, 25, 26, 27, 21};

auto heatWave = std::search_n(
    temperatures.begin(), temperatures.end(),
    3,
    24,
    [](int temp, int threshold) {
        return temp > threshold;
    }
);
```

`std::search_n` ищет `N` элементов подряд, равных значению или подходящих под бинарный предикат.

## Сравнение двух диапазонов

```cpp
std::vector<int> expected{1, 2, 3, 4};
std::vector<int> actual{1, 2, 5, 4};

auto [left, right] = std::mismatch(
    expected.begin(), expected.end(),
    actual.begin(), actual.end()
);
```

`std::mismatch` возвращает первую пару различающихся элементов.

Сложность — `O(min(N1, N2))`.

## Поиск в строке

`std::search` ищет одну последовательность внутри другой.

```cpp
#include <algorithm>
#include <functional>
#include <string_view>

std::string_view text = "the most efficient algorithm";
std::string_view word = "algorithm";

auto it = std::search(
    text.begin(), text.end(),
    std::boyer_moore_searcher(word.begin(), word.end())
);
```

Обычный `std::search` может работать за `O(N * M)`. Для строк и больших паттернов полезен `std::boyer_moore_searcher`, у него ожидаемая сложность ближе к `O(N + M)`.

## Подводные камни

## 1. Алгоритм не всегда быстрее

No raw loops повышает читаемость и снижает риск ошибок, но не гарантирует ускорение.

## 2. Нужно проверять `end`

```cpp
auto it = std::find(values.begin(), values.end(), 42);
if (it != values.end()) {
    // можно разыменовывать
}
```

Итератор `end()` нельзя разыменовывать.

## 3. `all_of`, `any_of`, `none_of` легко перепутать

Выбирай алгоритм по смыслу, а не через сложные отрицания.

```cpp
std::none_of(values.begin(), values.end(), isBad);
```

обычно читается лучше, чем:

```cpp
!std::any_of(values.begin(), values.end(), isBad);
```

## 4. `std::unique` и `adjacent_find` работают с соседями

Они не ищут все одинаковые элементы по всему контейнеру. Если нужны все дубликаты, часто сначала нужна сортировка.

## 5. Иногда цикл нормален

Если готовый алгоритм делает код запутаннее, оставь обычный цикл или вынеси логику в отдельную функцию.

## Саммари

- No raw loops заменяет ручные циклы готовыми STL-алгоритмами.
- `find`, `find_if`, `find_if_not` ищут первый подходящий элемент за `O(N)`.
- `all_of`, `any_of`, `none_of` проверяют факт выполнения условия.
- `search_n` ищет серию элементов подряд.
- `adjacent_find` ищет соседнюю пару.
- `mismatch` ищет первое различие двух диапазонов за `O(min(N1, N2))`.
- Для поиска подстрок можно использовать `std::search` и `std::boyer_moore_searcher`.
- Лямбды удобны для коротких условий.
