# 17. Удаление элемента из контейнера

## Суть

Удалять можно методом контейнера `erase` или алгоритмами стандартной библиотеки.

Для `std::vector` и других последовательных контейнеров до C++20 часто использовали идиому erase-remove. В C++20 проще применять `std::erase` и `std::erase_if`.

## Удаление по позиции

```cpp
#include <vector>

std::vector<int> values{1, 2, 3, 4, 5};

values.erase(values.begin() + 1);          // удалит 2
values.erase(std::next(values.begin()));   // то же самое
```

`std::next` и `std::advance` удобны, когда итератор не поддерживает `+ n`.

## std::remove и std::remove_if

`std::remove` и `std::remove_if` не уменьшают размер контейнера. Они переставляют оставшиеся элементы в начало диапазона и возвращают новый логический конец.

```cpp
#include <algorithm>
#include <vector>

std::vector<int> values{1, 2, 3, 2, 4};

auto newEnd = std::remove(values.begin(), values.end(), 2);

// size все еще 5
```

Чтобы удалить элементы физически, нужен `erase`.

## Идиома erase-remove

```cpp
std::vector<int> values{1, 2, 3, 2, 4};

values.erase(
    std::remove(values.begin(), values.end(), 2),
    values.end()
);
```

Сначала `remove` переносит ненужные элементы за новый логический конец, затем `erase` удаляет хвост.

Такой подход быстрее, чем удалять элементы из середины `vector` по одному в цикле.

## remove_if и предикаты

`std::remove_if` принимает унарный предикат.

```cpp
std::vector<int> values{1, 2, 3, 4, 5};

values.erase(
    std::remove_if(values.begin(), values.end(), [](int x) {
        return x % 2 == 0;
    }),
    values.end()
);
```

Предикатом может быть лямбда, функциональный объект или функция. Для одноразового условия обычно удобнее лямбда.

## Идиома unique-erase

`std::unique` тоже не удаляет элементы из контейнера. Он переносит соседние дубликаты за новый логический конец.

```cpp
#include <algorithm>
#include <vector>

std::vector<int> values{1, 2, 2, 3, 3, 4};

values.erase(std::unique(values.begin(), values.end()), values.end());
```

Если нужно удалить все дубликаты в произвольном порядке, сначала отсортируй контейнер.

## C++20: std::erase и std::erase_if

```cpp
#include <vector>

std::vector<int> values{1, 2, 3, 2, 4};

std::erase(values, 2);
std::erase_if(values, [](int x) {
    return x % 2 == 0;
});
```

`std::erase` удаляет элементы по значению. `std::erase_if` удаляет элементы по условию.

Для ассоциативных контейнеров используй `erase(key)` или `std::erase_if`.

```cpp
#include <map>
#include <string>

std::map<std::string, int> freq{{"apple", 3}, {"banana", 0}};

freq.erase("apple");
std::erase_if(freq, [](const auto& item) {
    return item.second == 0;
});
```

## Подводные камни

## 1. `remove` не удаляет

```cpp
std::remove(values.begin(), values.end(), 2);
```

Размер контейнера не изменится.

## 2. `unique` удаляет только соседние повторы

```cpp
std::vector<int> values{1, 2, 1};
values.erase(std::unique(values.begin(), values.end()), values.end());
```

Здесь оба `1` останутся, потому что они не рядом.

## 3. Удаление из середины `vector` дорогое

`vector::erase` сдвигает элементы правее удаленного места, поэтому удаление из середины стоит `O(N)`.

## 4. После `erase` нужен возвращенный итератор

```cpp
for (auto it = values.begin(); it != values.end();) {
    if (*it < 0) {
        it = values.erase(it);
    } else {
        ++it;
    }
}
```

Старый итератор после удаления использовать нельзя.

## 5. `std::erase` есть не для всех случаев

Для `map`, `set` и `unordered_*` удаление по ключу делает метод `erase(key)`, а удаление по условию — `std::erase_if`.

## Саммари

- `erase` реально уменьшает контейнер.
- `std::remove` и `std::remove_if` только переставляют элементы и возвращают новый логический конец.
- Erase-remove удаляет элементы из `vector` в два шага.
- `std::unique` работает так же: сначала логический конец, потом `erase`.
- В C++20 для простого удаления используй `std::erase` и `std::erase_if`.
- Для удаления в цикле продолжай обход с итератора, который вернул `erase`.
