# 16. Неупорядоченные ассоциативные контейнеры

## Суть

Неупорядоченные ассоциативные контейнеры хранят элементы в хеш-таблице.

Основные типы:

- `std::unordered_set` — уникальные ключи;
- `std::unordered_map` — пары ключ-значение с уникальным ключом;
- `std::unordered_multiset` — ключи с повторами;
- `std::unordered_multimap` — пары ключ-значение с повторами ключей.

Поиск, вставка и удаление обычно работают за `O(1)` в среднем. В худшем случае, при плохом распределении по корзинам, операции могут стать `O(N)`.

## Пример: unordered_set

```cpp
#include <unordered_set>

int main() {
    std::unordered_set<int> values{10, 20, 30};

    values.insert(20);      // повтор не добавится
    values.contains(10);    // true
    values.erase(30);
}
```

Порядок обхода не гарантирован.

## Пример: unordered_map

```cpp
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> age;

    age.emplace("Ann", 20);
    age["Bob"] = 30;

    auto it = age.find("Ann");
    if (it != age.end()) {
        ++it->second;
    }
}
```

`find`, `contains` и `count` не создают элемент. `operator[]` у `unordered_map` создает значение по умолчанию, если ключа нет.

## Хеш-таблица

Ключ сначала превращается в хеш через `Hash`, затем попадает в корзину (`bucket`). Если несколько ключей попали в одну корзину, контейнер сравнивает их через `KeyEqual`.

Полезные методы:

- `bucket_count()` — число корзин;
- `bucket(key)` — индекс корзины для ключа;
- `bucket_size(i)` — число элементов в корзине;
- `load_factor()` — `size() / bucket_count()`;
- `max_load_factor()` — порог загрузки перед повторным хешированием;
- `reserve(n)` — подготовить место под элементы;
- `rehash(n)` — запросить минимум `n` корзин.

```cpp
std::unordered_set<int> s{10, 20, 30};

s.reserve(100);
s.max_load_factor(0.7f);

auto buckets = s.bucket_count();
auto load = s.load_factor();
```

Обычно параметры по умолчанию достаточны. `reserve` полезен, когда заранее известен примерный объем данных.

## Контейнеры с повторами

`unordered_multiset` и `unordered_multimap` допускают несколько элементов с одинаковым ключом.

```cpp
std::unordered_multimap<std::string, int> scores;

scores.emplace("Ann", 10);
scores.emplace("Ann", 20);

auto [first, last] = scores.equal_range("Ann");
```

Для получения всех значений одного ключа используй `equal_range`.

## Пользовательские ключи

Для своего типа нужен хеш и сравнение на равенство.

```cpp
struct Point {
    int x;
    int y;

    bool operator==(const Point&) const = default;
};

struct PointHash {
    std::size_t operator()(const Point& p) const {
        auto h1 = std::hash<int>{}(p.x);
        auto h2 = std::hash<int>{}(p.y);
        return h1 ^ (h2 << 1);
    }
};

std::unordered_set<Point, PointHash> points;
```

Важно: если `a == b`, то хеши `a` и `b` должны быть равны.

## Гетерогенный поиск

В C++20 можно искать не только по `Key`, если `Hash` и `KeyEqual` прозрачные.

```cpp
struct MyId {
    int id;
    std::string name;
};

struct MyIdHash {
    using is_transparent = void;

    std::size_t operator()(const MyId& key) const {
        return std::hash<int>{}(key.id);
    }

    std::size_t operator()(int id) const {
        return std::hash<int>{}(id);
    }
};

struct MyIdEqual {
    using is_transparent = void;

    bool operator()(const MyId& lhs, const MyId& rhs) const {
        return lhs.id == rhs.id;
    }

    bool operator()(const MyId& lhs, int rhs) const {
        return lhs.id == rhs;
    }

    bool operator()(int lhs, const MyId& rhs) const {
        return rhs.id == lhs;
    }
};

std::unordered_set<MyId, MyIdHash, MyIdEqual> ids;
auto it = ids.find(42);
```

Для гетерогенных операций нужны и прозрачный хешер, и прозрачное сравнение.

## Инвалидация

- `insert` и `emplace` могут вызвать `rehash` и инвалидировать итераторы;
- `rehash`, `reserve`, присваивание инвалидируют итераторы;
- `erase` инвалидирует только итераторы и ссылки на удаленные элементы;
- ссылки и указатели на неудаленные элементы обычно сохраняются даже после `rehash`.

## Подводные камни

## 1. Порядка нет

Не используй `unordered_*`, если нужен отсортированный обход, поиск диапазона или следующий элемент по порядку.

## 2. Хеш может испортить сложность

Если много элементов попадает в одну корзину, `O(1)` превращается в `O(N)`.

## 3. Памяти обычно нужно больше

Хеш-таблица хранит корзины и узлы, поэтому часто расходует больше памяти, чем кажется.

## 4. `operator[]` меняет контейнер

Для проверки ключа используй `find`, `contains` или `at`.

## 5. `rehash` ломает итераторы

Не сохраняй итераторы через операции, которые могут изменить число корзин.

## Саммари

- `unordered_set`, `unordered_map`, `unordered_multiset`, `unordered_multimap` основаны на хеш-таблице.
- Поиск, вставка и удаление в среднем стоят `O(1)`, в худшем случае — `O(N)`.
- Элементы лежат в корзинах, загрузку контролируют `load_factor`, `max_load_factor`, `reserve`, `rehash`.
- Порядок обхода не гарантирован и может измениться после `rehash`.
- Для пользовательского ключа нужны согласованные хеш и равенство.
- Для гетерогенного поиска нужны прозрачные `Hash` и `KeyEqual`.
- `std::map` удобнее для порядка и диапазонов, `std::unordered_map` — для быстрого доступа по ключу на больших данных.
