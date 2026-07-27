# 18. Концепция no raw loops

## Суть

No raw loops - идея не писать ручной цикл там, где есть готовый алгоритм.

Алгоритм лучше показывает намерение.

```cpp
std::find(values.begin(), values.end(), 42);
```

Вместо ручного перебора.

## Пример 1: поиск

```cpp
bool has_value(const std::vector<int>& values, int target) {
    return std::find(values.begin(), values.end(), target) != values.end();
}
```

Сразу видно: ищем значение.

## Пример 2: проверка условия

```cpp
bool all_positive(const std::vector<int>& values) {
    return std::all_of(values.begin(), values.end(), [](int x) {
        return x > 0;
    });
}
```

Сразу видно: все элементы должны быть положительными.

## Пример 3: преобразование

```cpp
std::vector<int> result;
result.resize(values.size());

std::transform(values.begin(), values.end(), result.begin(), [](int x) {
    return x * 2;
});
```

Алгоритм отделяет обход от действия.

## Пример 4: сортировка

```cpp
std::sort(values.begin(), values.end());
```

Не нужно писать свою сортировку для обычного случая.

## Подводные камни

## 1. Не любой цикл нужно прятать

Если логика сложная и алгоритм ухудшает читаемость, обычный цикл нормален.

## 2. Нужно знать границы

```cpp
std::find(values.begin(), values.end(), x);
```

Алгоритмы работают с диапазоном `[begin, end)`.

`end` не входит в диапазон.

## 3. Лямбда должна быть простой

```cpp
std::any_of(values.begin(), values.end(), [](int x) {
    return x > 10;
});
```

Если внутри лямбды много логики, лучше вынести функцию.

## 4. В C++20 есть ranges

```cpp
std::ranges::find(values, 42);
```

Ranges часто короче и безопаснее.

## Саммари

- No raw loops предлагает использовать стандартные алгоритмы.
- Алгоритмы лучше выражают намерение.
- Диапазон обычно задается как `[begin, end)`.
- Ручной цикл допустим, если он читабельнее.
- В C++20 стоит смотреть на `std::ranges`.
