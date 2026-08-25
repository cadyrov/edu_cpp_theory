# 20. Категория алгоритмов, меняющих порядок

## Суть

Алгоритмы этой категории переставляют элементы внутри диапазона.

Они помогают сортировать, выбирать топ элементов, находить медиану, разворачивать, сдвигать и циклически переносить элементы без ручных циклов.

## sort и stable_sort

`std::sort` сортирует диапазон за `O(N log N)`, но не сохраняет порядок равных элементов.

```cpp
#include <algorithm>
#include <vector>

std::vector<int> values{3, 1, 2};
std::sort(values.begin(), values.end());
```

`std::stable_sort` сохраняет относительный порядок элементов, которые равны по ключу сортировки.

```cpp
struct Product {
    int price;
    int originalIndex;
};

std::stable_sort(products.begin(), products.end(), [](const Product& lhs, const Product& rhs) {
    return lhs.price < rhs.price;
});
```

Используй `stable_sort`, когда сортировка идет в несколько шагов и предыдущий порядок важен.

## partial_sort

`std::partial_sort` сортирует только первые `M` элементов диапазона.

```cpp
std::vector<int> values{9, 4, 3, 7, 1, 8, 2};

std::partial_sort(values.begin(), values.begin() + 3, values.end());
```

После вызова первые три элемента — три наименьших значения, отсортированные между собой.

Сложность примерно `O(N log M)`, что выгодно для топ-N.

## nth_element

`std::nth_element` ставит элемент на позицию, где он был бы после полной сортировки.

```cpp
std::vector<int> values{9, 4, 3, 7, 1, 8, 2};

auto mid = values.begin() + values.size() / 2;
std::nth_element(values.begin(), mid, values.end());
```

Все элементы слева от `mid` не больше него, все элементы справа — не меньше. При этом части не обязаны быть отсортированы.

Средняя сложность — `O(N)`.

## reverse и reverse_copy

`std::reverse` разворачивает диапазон на месте.

```cpp
std::vector<int> values{1, 2, 3, 4};
std::reverse(values.begin(), values.end());
```

`std::reverse_copy` записывает развернутую копию в другой диапазон.

```cpp
std::vector<int> source{1, 2, 3, 4};
std::vector<int> destination(source.size());

std::reverse_copy(source.begin(), source.end(), destination.begin());
```

## shift_left и shift_right

`std::shift_left` и `std::shift_right` сдвигают элементы на заданное число позиций.

```cpp
std::vector<int> values{1, 2, 3, 4, 5};

std::shift_left(values.begin(), values.end(), 2);
```

Это не циклический сдвиг. Элементы, вытесненные за границу диапазона, теряются, а освободившиеся позиции не имеют полезного гарантированного значения.

Сложность — `O(N - k)`.

## rotate

`std::rotate` циклически переставляет две части диапазона.

```cpp
std::vector<int> values{1, 2, 3, 4, 5};

std::rotate(values.begin(), values.begin() + 2, values.end());
// 3 4 5 1 2
```

Алгоритм принимает `first`, `mid`, `last`: элемент `mid` становится первым, а порядок внутри частей сохраняется.

Сложность — `O(N)`.

## Подводные камни

## 1. `sort` нестабилен

Если порядок равных элементов важен, используй `std::stable_sort`.

## 2. `partial_sort` не сортирует хвост

После `partial_sort(first, middle, last)` отсортирован только диапазон `[first, middle)`.

## 3. `nth_element` не сортирует диапазон

Он гарантирует только правильную позицию `nth` и разделение на меньшие и большие элементы.

## 4. `shift_left` и `shift_right` не rotate

Не полагайся на значения в освободившихся позициях.

## 5. Алгоритмы меняют исходный контейнер

Если исходный порядок нужен дальше, сделай копию или используй алгоритм с суффиксом `_copy`.

## Саммари

- `std::sort` — быстрая полная сортировка за `O(N log N)`.
- `std::stable_sort` сохраняет порядок равных элементов.
- `std::partial_sort` сортирует только первые `M` элементов за `O(N log M)`.
- `std::nth_element` находит позицию n-го элемента без полной сортировки.
- `std::reverse` разворачивает диапазон, `reverse_copy` пишет результат в другой диапазон.
- `std::shift_left` и `shift_right` сдвигают элементы без цикличности.
- `std::rotate` циклически переносит часть диапазона и сохраняет относительный порядок.
