# 19. Алгоритмы поиска в стандартной библиотеке

## Суть

Стандартная библиотека содержит готовые алгоритмы поиска.

Они работают с итераторами и не зависят от конкретного контейнера.

Основные:

- `std::find`;
- `std::find_if`;
- `std::any_of`;
- `std::all_of`;
- `std::none_of`;
- `std::binary_search`;
- `std::lower_bound`;
- `std::upper_bound`.

## Пример 1: find

```cpp
auto it = std::find(values.begin(), values.end(), 42);

if (it != values.end()) {
    std::cout << "found\n";
}
```

Ищет конкретное значение.

## Пример 2: find_if

```cpp
auto it = std::find_if(values.begin(), values.end(), [](int x) {
    return x % 2 == 0;
});
```

Ищет первый элемент по условию.

## Пример 3: any_of

```cpp
bool has_negative = std::any_of(values.begin(), values.end(), [](int x) {
    return x < 0;
});
```

Проверяет, есть ли хотя бы один подходящий элемент.

## Пример 4: binary_search

```cpp
std::sort(values.begin(), values.end());

bool found = std::binary_search(values.begin(), values.end(), 42);
```

Работает только на отсортированном диапазоне.

## Пример 5: lower_bound

```cpp
auto it = std::lower_bound(values.begin(), values.end(), 42);
```

Возвращает первую позицию, куда можно вставить `42`, не ломая сортировку.

## Подводные камни

## 1. Проверять нужно с end()

```cpp
if (it != values.end()) {
    // нашли
}
```

Если ничего не найдено, алгоритм вернет конец диапазона.

## 2. binary_search требует сортировки

```cpp
std::binary_search(values.begin(), values.end(), x);
```

На неотсортированных данных результат некорректен.

## 3. lower_bound не говорит "найдено"

```cpp
auto it = std::lower_bound(values.begin(), values.end(), x);

if (it != values.end() && *it == x) {
    // найдено
}
```

Он возвращает позицию, а не булев ответ.

## 4. map имеет собственный find

```cpp
auto it = m.find(key);
```

Для `map` и `unordered_map` обычно лучше метод контейнера.

## Саммари

- `find` ищет значение.
- `find_if` ищет по условию.
- `any_of`, `all_of`, `none_of` проверяют диапазон.
- `binary_search` работает только на отсортированном диапазоне.
- `lower_bound` возвращает позицию вставки.
- Для ассоциативных контейнеров часто лучше использовать их `find`.
