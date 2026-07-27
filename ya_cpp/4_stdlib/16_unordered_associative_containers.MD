# 16. Неупорядоченные ассоциативные контейнеры

## Суть

Неупорядоченные ассоциативные контейнеры используют хеш-таблицу.

Основные типы:

- `std::unordered_set`;
- `std::unordered_map`;
- `std::unordered_multiset`;
- `std::unordered_multimap`.

Обычно поиск, вставка и удаление работают за `O(1)` в среднем.

## Пример 1: unordered_set

```cpp
#include <iostream>
#include <unordered_set>

int main() {
    std::unordered_set<int> values{10, 20, 30};

    if (values.contains(20)) {
        std::cout << "found\n";
    }
}
```

Порядок обхода не гарантирован.

## Пример 2: unordered_map

```cpp
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> age;

    age["Ann"] = 20;
    age["Bob"] = 30;

    std::cout << age["Bob"] << '\n';
}
```

Ключ превращается в хеш, по которому выбирается корзина.

## Пример 3: find

```cpp
auto it = age.find("Bob");
if (it != age.end()) {
    std::cout << it->second << '\n';
}
```

`find` не создает элемент.

## Подводные камни

## 1. Порядка нет

```cpp
for (const auto& [key, value] : age) {
    std::cout << key << '\n';
}
```

Порядок вывода не нужно считать стабильным или отсортированным.

## 2. operator[] создает элемент

```cpp
std::unordered_map<std::string, int> age;

age["Unknown"]; // создает пару
```

Для проверки используй `find` или `contains`.

## 3. Худший случай может быть O(n)

Если много ключей попали в одну корзину, операции становятся медленнее.

В среднем обычно `O(1)`.

## 4. rehash инвалидирует итераторы

```cpp
auto it = values.begin();

values.insert(42); // может вызвать rehash

// it может стать невалидным
```

При изменении числа корзин итераторы ломаются.

## 5. Для своего ключа нужен hash

```cpp
struct Point {
    int x;
    int y;
};
```

Чтобы использовать `Point` как ключ, нужно задать равенство и хеш.

## Саммари

- `unordered_map` и `unordered_set` используют хеш-таблицу.
- Порядок элементов не гарантирован.
- Операции обычно `O(1)` в среднем.
- `operator[]` у map создает элемент.
- `rehash` может инвалидировать итераторы.
- Для пользовательских ключей нужен корректный хеш и сравнение на равенство.
