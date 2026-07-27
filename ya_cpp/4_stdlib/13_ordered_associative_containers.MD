# 13. Упорядоченные ассоциативные контейнеры

## Суть

Упорядоченные ассоциативные контейнеры хранят элементы отсортированными по ключу.

Основные типы:

- `std::set`;
- `std::map`;
- `std::multiset`;
- `std::multimap`.

Обычно операции поиска, вставки и удаления стоят `O(log n)`.

## Пример 1: set

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> values{30, 10, 20, 10};

    for (int value : values) {
        std::cout << value << ' ';
    }
}
```

Вывод:

```text
10 20 30
```

`set` хранит уникальные ключи.

## Пример 2: map

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> age;

    age["Ann"] = 20;
    age["Bob"] = 30;

    std::cout << age["Ann"] << '\n';
}
```

`map` хранит пары ключ-значение.

## Пример 3: find

```cpp
auto it = age.find("Bob");
if (it != age.end()) {
    std::cout << it->second << '\n';
}
```

`find` не создает новый элемент.

## Подводные камни

## 1. operator[] у map создает элемент

```cpp
std::map<std::string, int> age;

std::cout << age["Unknown"]; // создаст ключ "Unknown" со значением 0
```

Для проверки лучше использовать `find` или `contains`.

## 2. Ключи нельзя менять на месте

```cpp
std::set<int> values{1, 2, 3};
auto it = values.find(2);

// *it = 5; // ошибка
```

Изменение ключа сломало бы порядок контейнера.

## 3. Порядок задает сравнение

```cpp
std::set<std::string, std::less<>> names;
```

Два ключа считаются одинаковыми, если сравнение не ставит ни один меньше другого.

## 4. Это не хеш-таблица

`std::map` и `std::set` хранят порядок.

Если порядок не нужен, иногда лучше `std::unordered_map`.

## Саммари

- `set` хранит уникальные ключи.
- `map` хранит ключ-значение.
- Элементы упорядочены по ключу.
- Поиск, вставка и удаление обычно `O(log n)`.
- `map::operator[]` может создать новый элемент.
- Ключ нельзя менять прямо внутри контейнера.
