# 17. Удаление элемента из контейнера

## Суть

Удаление зависит от контейнера.

Для последовательных контейнеров часто используют `erase`.

Для удаления по условию в `vector` классический прием - erase-remove.

## Пример 1: удалить по позиции

```cpp
std::vector<int> values{10, 20, 30};

values.erase(values.begin() + 1);
```

Удалится `20`.

## Пример 2: erase-remove

```cpp
#include <algorithm>
#include <vector>

std::vector<int> values{1, 2, 3, 2, 4};

values.erase(
    std::remove(values.begin(), values.end(), 2),
    values.end()
);
```

`std::remove` сдвигает нужные элементы в начало и возвращает новый логический конец.

`erase` реально уменьшает контейнер.

## Пример 3: erase_if

```cpp
#include <vector>

std::vector<int> values{1, 2, 3, 4};

std::erase_if(values, [](int x) {
    return x % 2 == 0;
});
```

С C++20 есть готовый `std::erase_if`.

## Пример 4: map/set

```cpp
std::map<std::string, int> age;

age.erase("Bob");
```

В ассоциативных контейнерах можно удалять по ключу.

## Подводные камни

## 1. remove не удаляет из контейнера

```cpp
std::remove(values.begin(), values.end(), 2);
```

Размер `values` не изменится.

Нужен `erase`.

## 2. Нельзя продолжать со стертым итератором

```cpp
it = values.erase(it);
```

`erase` возвращает следующий корректный итератор.

## 3. Удаление из vector сдвигает элементы

Удаление из середины `vector` стоит `O(n)`.

## 4. Удаление в цикле требует аккуратности

```cpp
for (auto it = values.begin(); it != values.end();) {
    if (*it == 0) {
        it = values.erase(it);
    } else {
        ++it;
    }
}
```

## Саммари

- `erase` реально удаляет элементы из контейнера.
- `std::remove` только переставляет элементы.
- Для `vector` часто нужен erase-remove.
- В C++20 есть `std::erase` и `std::erase_if`.
- После удаления по итератору используй возвращенный итератор.
