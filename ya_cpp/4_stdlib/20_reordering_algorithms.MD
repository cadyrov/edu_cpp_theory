# 20. Категория алгоритмов, меняющих порядок

## Суть

Есть алгоритмы, которые переставляют элементы в диапазоне.

Они не создают новый контейнер, а меняют порядок существующих элементов.

Примеры:

- `std::sort`;
- `std::stable_sort`;
- `std::reverse`;
- `std::rotate`;
- `std::shuffle`;
- `std::partition`.

## Пример 1: sort

```cpp
std::vector<int> values{3, 1, 2};

std::sort(values.begin(), values.end());
```

После сортировки: `1 2 3`.

## Пример 2: reverse

```cpp
std::vector<int> values{1, 2, 3};

std::reverse(values.begin(), values.end());
```

После разворота: `3 2 1`.

## Пример 3: rotate

```cpp
std::vector<int> values{1, 2, 3, 4};

std::rotate(values.begin(), values.begin() + 1, values.end());
```

После поворота: `2 3 4 1`.

## Пример 4: partition

```cpp
std::vector<int> values{1, 2, 3, 4, 5};

auto middle = std::partition(values.begin(), values.end(), [](int x) {
    return x % 2 == 0;
});
```

Сначала будут элементы, подходящие под условие.

Порядок внутри групп не гарантирован.

## Подводные камни

## 1. sort требует random access iterators

```cpp
std::list<int> values{3, 1, 2};

// std::sort(values.begin(), values.end()); // ошибка
values.sort(); // ok
```

`std::sort` не работает с `std::list`.

## 2. stable_sort сохраняет порядок равных

```cpp
std::stable_sort(values.begin(), values.end(), cmp);
```

Если важен порядок равных элементов, нужен `stable_sort`.

## 3. partition не сортирует

Он только делит диапазон на две группы.

Внутри групп порядок может измениться.

## 4. Алгоритмы меняют исходные данные

```cpp
std::sort(values.begin(), values.end());
```

После вызова старого порядка уже нет.

Если он нужен, сначала сделай копию.

## Саммари

- Алгоритмы этой категории переставляют элементы.
- `sort` сортирует диапазон.
- `reverse` разворачивает диапазон.
- `rotate` переносит часть диапазона.
- `partition` делит элементы по условию.
- Не каждый алгоритм работает с каждым типом итератора.
