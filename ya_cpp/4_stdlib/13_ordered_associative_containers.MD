# 13. Упорядоченные ассоциативные контейнеры

## Суть

Упорядоченные ассоциативные контейнеры хранят элементы отсортированными по ключу.

Основные типы:

- `std::set` - уникальные ключи;
- `std::map` - уникальные ключи и значения;
- `std::multiset` - ключи с повторами;
- `std::multimap` - ключи с повторами и значения.

Обычно поиск, вставка, удаление и переход к следующему/предыдущему элементу стоят `O(log N)`.

## Устройство

Обычно `std::map`, `std::set`, `std::multimap` и `std::multiset` реализованы как самобалансирующееся дерево.

Частый вариант - красно-черное дерево.

Балансировка нужна, чтобы высота дерева росла логарифмически.

Поэтому операции остаются `O(log N)` даже при большом количестве элементов.

## set

```cpp
#include <set>

std::set<int> values;

values.insert(30);
values.insert(10);
values.insert(20);
values.insert(10);
```

В контейнере будут значения:

```text
10 20 30
```

`set` хранит уникальные ключи.

Повторная вставка уже существующего ключа не добавит новый элемент.

## map

```cpp
#include <map>
#include <string>

std::map<std::string, int> age;

age.insert({"Ann", 20});
age["Bob"] = 30;
```

`map` хранит пары ключ-значение.

Тип элемента внутри `std::map<Key, T>` - `std::pair<const Key, T>`.

Ключ внутри элемента менять нельзя, иначе сломается порядок дерева.

## find, contains, count

```cpp
auto it = age.find("Bob");
if (it != age.end()) {
    std::cout << it->second << '\n';
}
```

`find` возвращает итератор или `end()`.

```cpp
age.contains("Ann");
age.count("Ann");
```

Для `set` и `map` `count` возвращает `0` или `1`.

Для `multiset` и `multimap` может вернуть больше.

## operator[] и at

`map::operator[]` создает элемент, если ключа нет.

```cpp
std::map<std::string, int> age;

age["Unknown"]; // создаст ключ "Unknown" со значением 0
```

`at()` не создает элемент.

```cpp
age.at("Unknown"); // std::out_of_range
```

`operator[]` нельзя использовать с `const std::map`, потому что он возвращает изменяемую ссылку.

Для проверки лучше использовать `find` или `contains`.

## multimap и multiset

`multi`-контейнеры разрешают несколько элементов с одинаковым ключом.

```cpp
std::multimap<std::string, int> scores;

scores.insert({"Alice", 70});
scores.insert({"Alice", 80});
```

Чтобы получить все элементы по ключу, используют `equal_range`.

```cpp
auto [first, last] = scores.equal_range("Alice");

for (auto it = first; it != last; ++it) {
    std::cout << it->second << '\n';
}
```

У `multimap` нет `operator[]`, потому что по одному ключу может быть несколько значений.

## Пользовательские типы

Чтобы хранить свой тип в `std::set`, нужно задать порядок.

```cpp
struct Person {
    std::string name;
    int age;

    bool operator<(const Person& other) const {
        if (name != other.name) {
            return name < other.name;
        }
        return age < other.age;
    }
};

std::set<Person> persons;
```

В C++20 часто проще использовать `<=>`.

```cpp
struct Person {
    std::string name;
    int age;

    auto operator<=>(const Person&) const = default;
};
```

Порядок сравнения полей идет в порядке объявления.

## Пользовательский компаратор

Если тип менять нельзя или нужен другой порядок, используют компаратор.

```cpp
struct PersonByName {
    bool operator()(const Person& lhs, const Person& rhs) const {
        return lhs.name < rhs.name;
    }
};

std::set<Person, PersonByName> persons;
```

Важно: уникальность в `set` определяется компаратором.

Если компаратор сравнивает только `name`, то два `Person` с одинаковым именем считаются одним ключом.

## Вставка в map

Есть несколько способов вставить элемент.

```cpp
std::map<int, User> users;

users.insert({1, User{"Ann", 20}});
users.emplace(2, User{"Bob", 30});
users.try_emplace(3, "Mary", 25);
users.insert_or_assign(2, User{"Bob", 31});
```

`insert` принимает готовый элемент.

`emplace` строит элемент внутри контейнера, но значение иногда все равно приходится создать заранее.

`try_emplace` строит значение на месте, только если ключа еще нет.

`insert_or_assign` вставляет новый элемент или перезаписывает значение по существующему ключу.

## piecewise_construct

`std::piecewise_construct` позволяет отдельно передать аргументы для ключа и значения внутри `std::pair`.

```cpp
users.emplace(
    std::piecewise_construct,
    std::forward_as_tuple(1),
    std::forward_as_tuple("Ann", 20)
);
```

Это уменьшает лишние временные объекты, но код громоздкий.

В C++17 обычно удобнее `try_emplace`.

```cpp
users.try_emplace(1, "Ann", 20);
```

## node handle и extract

Ключ в `map` менять напрямую нельзя.

Но можно извлечь узел, изменить ключ и вставить обратно.

```cpp
std::map<int, std::string> values{{1, "one"}, {2, "two"}};

auto node = values.extract(2);
node.key() = 3;
node.mapped() = "three";

values.insert(std::move(node));
```

`extract` не перемещает ключ и значение.

Он отдает node handle, которому временно принадлежит узел дерева.

## Гетерогенный поиск

Обычный `find` ищет по типу ключа.

Иногда создание полноценного ключа дорого.

Гетерогенный поиск позволяет искать по другому типу без временного объекта ключа.

```cpp
struct Id {
    int value;

    auto operator<=>(const Id&) const = default;
    friend auto operator<=>(const Id& lhs, int rhs) {
        return lhs.value <=> rhs;
    }
    friend auto operator<=>(int lhs, const Id& rhs) {
        return lhs <=> rhs.value;
    }
};

std::map<Id, std::string, std::less<>> names;

auto it = names.find(42);
```

Здесь важен `std::less<>`, а не `std::less<Id>`.

`std::less<>` - прозрачный компаратор. У него есть `is_transparent`, поэтому перегрузки `find(K)`, `contains(K)`, `count(K)` могут участвовать в overload resolution.

## Свой прозрачный компаратор

Можно задать гетерогенный поиск только внутри конкретного контейнера.

```cpp
struct ByName {
    using is_transparent = void;

    bool operator()(const Person& lhs, const Person& rhs) const {
        return lhs.name < rhs.name;
    }

    bool operator()(const Person& lhs, std::string_view rhs) const {
        return lhs.name < rhs;
    }

    bool operator()(std::string_view lhs, const Person& rhs) const {
        return lhs < rhs.name;
    }
};

std::set<Person, ByName> persons;

persons.find("Ann");
```

Требования:

- компаратор содержит `using is_transparent = void`;
- ключ сравним с типом аргумента поиска в обе стороны;
- контейнер создан именно с этим компаратором.

## Подводные камни

## 1. operator[] создает элемент

```cpp
std::map<std::string, int> age;

age["Unknown"]; // вставка
```

Если нужна только проверка, используй `find` или `contains`.

## 2. Ключи нельзя менять на месте

```cpp
std::set<int> values{1, 2, 3};
auto it = values.find(2);

// *it = 5; // ошибка
```

Для `map` ключ в паре имеет тип `const Key`.

## 3. Уникальность задает компаратор

```cpp
struct ByName {
    bool operator()(const Person& lhs, const Person& rhs) const {
        return lhs.name < rhs.name;
    }
};
```

Если два объекта эквивалентны по компаратору, `set` считает их одним ключом.

## 4. multimap не имеет operator[]

По одному ключу может быть несколько значений.

Используй `equal_range`.

## 5. Гетерогенный поиск требует прозрачный компаратор

```cpp
std::map<Id, std::string> a;
std::map<Id, std::string, std::less<>> b;
```

Гетерогенный `find(42)` заработает только во втором случае, если сравнения с `int` определены.

## 6. Это не хеш-таблица

`std::map` и `std::set` хранят порядок.

Если порядок не нужен, иногда лучше `std::unordered_map`.

## Саммари

- Упорядоченные ассоциативные контейнеры хранят элементы по ключу в отсортированном порядке.
- `set` хранит уникальные ключи.
- `map` хранит пары ключ-значение.
- `multiset` и `multimap` разрешают повторяющиеся ключи.
- Обычно внутри используется самобалансирующееся дерево.
- Поиск, вставка и удаление обычно `O(log N)`.
- `size()` работает за `O(1)`.
- `map::operator[]` может создать новый элемент.
- `at()` не создает элемент и бросает `std::out_of_range`.
- Уникальность определяется компаратором.
- Пользовательский тип должен иметь порядок: `operator<`, `<=>` или компаратор.
- `try_emplace` строит значение на месте, если ключа еще нет.
- `insert_or_assign` вставляет или обновляет значение.
- `piecewise_construct` разделяет аргументы ключа и значения.
- `extract` позволяет изменить ключ без пересоздания узла.
- Гетерогенный поиск ищет по типу, отличному от типа ключа.
- Для гетерогенного поиска нужен прозрачный компаратор: `std::less<>` или свой с `is_transparent`.
