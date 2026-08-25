# 19. Алгоритмы поиска в стандартной библиотеке

## Суть

Стандартная библиотека дает готовые алгоритмы поиска по диапазонам.

Часть алгоритмов ищет линейно, часть требует отсортированный диапазон и работает через бинарный поиск.

## Поиск подпоследовательности

`std::search` ищет первое вхождение одной последовательности в другой.

```cpp
#include <algorithm>
#include <vector>

std::vector<int> values{21, 22, 23, 19, 21, 22, 23};
std::vector<int> pattern{21, 22, 23};

auto first = std::search(
    values.begin(), values.end(),
    pattern.begin(), pattern.end()
);
```

`std::find_end` ищет последнее вхождение подпоследовательности.

```cpp
auto last = std::find_end(
    values.begin(), values.end(),
    pattern.begin(), pattern.end()
);
```

В худшем случае такие алгоритмы могут работать за `O(N * M)`.

## Поиск любого элемента из набора

`std::find_first_of` ищет первый элемент первого диапазона, который равен любому элементу второго диапазона.

```cpp
#include <algorithm>
#include <string>

std::string text = "hello @ world";
std::string special = "@#$%";

auto it = std::find_first_of(
    text.begin(), text.end(),
    special.begin(), special.end()
);
```

Сложность — `O(N * M)`: для каждого элемента первого диапазона проверяются элементы второго.

Если второй набор большой, его можно положить в `std::unordered_set` и искать через `std::find_if`.

```cpp
#include <unordered_set>

std::unordered_set<char> specialSet(special.begin(), special.end());

auto fast = std::find_if(text.begin(), text.end(), [&specialSet](char c) {
    return specialSet.contains(c);
});
```

Подготовка стоит `O(M)`, поиск — `O(N)` в среднем.

## Сортировка перед поиском

Бинарный поиск работает только на отсортированном диапазоне.

```cpp
#include <algorithm>
#include <vector>

std::vector<int> numbers{7, 3, 9, 2, 5, 1};

std::sort(numbers.begin(), numbers.end());
```

`std::sort` обычно лучше `qsort` из C:

- типобезопасен;
- работает с итераторами;
- принимает лямбды и функциональные объекты;
- часто быстрее из-за инлайнинга компаратора.

Сложность `std::sort` — `O(N log N)`.

## Компараторы

```cpp
std::sort(numbers.begin(), numbers.end(), std::greater<int>{});
```

Такой компаратор сортирует по убыванию.

```cpp
std::sort(numbers.begin(), numbers.end(), [](int lhs, int rhs) {
    return std::abs(lhs) < std::abs(rhs);
});
```

Компаратор должен задавать строгий порядок.

## Бинарный поиск

`std::binary_search` отвечает только на вопрос, есть ли элемент.

```cpp
bool found = std::binary_search(numbers.begin(), numbers.end(), 5);
```

`std::lower_bound` возвращает первый элемент, который не меньше значения.

```cpp
auto lower = std::lower_bound(numbers.begin(), numbers.end(), 5);
```

`std::upper_bound` возвращает первый элемент, который строго больше значения.

```cpp
auto upper = std::upper_bound(numbers.begin(), numbers.end(), 5);
```

`std::equal_range` возвращает диапазон всех элементов, равных значению.

```cpp
auto [first, last] = std::equal_range(numbers.begin(), numbers.end(), 5);
auto count = std::distance(first, last);
```

`lower_bound`, `upper_bound`, `equal_range` работают за `O(log N)` на отсортированном диапазоне.

## Подводные камни

## 1. Бинарный поиск требует сортировки

На неотсортированном диапазоне результат `binary_search`, `lower_bound`, `upper_bound` и `equal_range` некорректен.

## 2. `lower_bound` не равен `find`

```cpp
auto it = std::lower_bound(numbers.begin(), numbers.end(), x);
if (it != numbers.end() && *it == x) {
    // x найден
}
```

Нужно отдельно проверить, что найденный элемент действительно равен `x`.

## 3. Компаратор должен совпадать

Если сортировали с компаратором, искать нужно с тем же правилом сравнения.

## 4. `find_first_of` может быть дорогим

При больших диапазонах `O(N * M)` быстро становится проблемой. Часто помогает `unordered_set`.

## 5. `std::sort` нестабилен

Он не обязан сохранять порядок равных элементов. Если это важно, используй `std::stable_sort`.

## Саммари

- `std::search` ищет первое вхождение подпоследовательности.
- `std::find_end` ищет последнее вхождение подпоследовательности.
- `std::find_first_of` ищет первый элемент из набора и стоит `O(N * M)`.
- Поиск можно ускорить через подготовку данных: `unordered_set` или сортировку.
- `std::sort` сортирует за `O(N log N)` и обычно удобнее `qsort`.
- `binary_search`, `lower_bound`, `upper_bound`, `equal_range` требуют отсортированный диапазон.
- Бинарный поиск работает за `O(log N)`.
