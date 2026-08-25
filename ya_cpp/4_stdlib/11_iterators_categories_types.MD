# 11. Итераторы: категории, свойства и типы

## Суть

Итератор - объект, который дает доступ к элементу последовательности и умеет переходить к другим элементам.

Он похож на обобщенный указатель.

```cpp
auto it = values.begin();
```

Итераторы позволяют писать алгоритмы один раз, а применять к разным контейнерам.

Алгоритму не важно, где лежат элементы: в `std::vector`, `std::list`, `std::deque` или другом контейнере.

## Минимальный интерфейс

Обычно итератор поддерживает:

- `operator*` - получить элемент;
- `operator++` - перейти к следующему;
- `operator==` или `operator!=` - сравнить с другим итератором.

```cpp
auto it = values.begin();

std::cout << *it << '\n';
++it;
```

Для объектов часто есть `operator->`.

```cpp
auto it = users.begin();

std::cout << it->name << '\n';
```

## begin/end

`begin()` возвращает итератор на первый элемент.

`end()` возвращает итератор на позицию после последнего элемента.

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> values{10, 20, 30};

    for (auto it = values.begin(); it != values.end(); ++it) {
        std::cout << *it << ' ';
    }
}
```

`end()` нельзя разыменовывать.

```cpp
auto it = values.end();

// std::cout << *it; // undefined behavior
```

Для пустого контейнера `begin() == end()`.

## Категории итераторов

Категория итератора определяет, какие операции доступны и какие алгоритмы можно применять.

- input iterator - читать последовательность вперед один раз;
- output iterator - писать значения вперед;
- forward iterator - идти вперед и читать многократно;
- bidirectional iterator - идти вперед и назад;
- random access iterator - прыгать на произвольное смещение;
- contiguous iterator - random access плюс элементы лежат подряд в памяти.

Категории образуют иерархию: более сильный итератор умеет все, что умеют более слабые категории ниже.

## InputIterator

Input iterator нужен для однократного чтения входной последовательности.

Пример - `std::istream_iterator`.

```cpp
#include <iostream>
#include <iterator>

std::istream_iterator<int> it(std::cin);
std::istream_iterator<int> end;

int sum = 0;
while (it != end) {
    sum += *it;
    ++it;
}
```

Такую последовательность нельзя надежно пройти заново тем же способом.

## ForwardIterator

Forward iterator идет только вперед, но последовательность можно проходить многократно.

Пример - `std::forward_list`.

```cpp
std::forward_list<int> values{1, 2, 3};

auto it = values.begin();
++it;
```

Назад идти нельзя.

```cpp
// --it; // ошибка
```

## BidirectionalIterator

Bidirectional iterator умеет идти вперед и назад.

Пример - `std::list`.

```cpp
std::list<int> values{1, 2, 3};

auto it = values.begin();
++it;
--it;
```

Но произвольного доступа нет.

```cpp
// it += 2; // ошибка
```

## RandomAccessIterator

Random access iterator умеет быстро прыгать по смещению.

Пример - `std::deque`.

```cpp
std::deque<int> values{10, 20, 30};

auto it = values.begin();
it += 2;
```

Такой итератор поддерживает:

- `it + n`;
- `it - n`;
- `it1 - it2`;
- `it[n]`;
- сравнения `<`, `>`, `<=`, `>=`.

## ContiguousIterator

Contiguous iterator означает, что элементы лежат подряд в памяти.

Примеры:

- `std::array`;
- `std::vector`;
- `std::string`;
- `std::span`.

```cpp
std::vector<int> values{1, 2, 3};

int* p = std::to_address(values.begin());
```

`std::deque` имеет random access iterator, но не contiguous iterator.

У него есть доступ по индексу, но элементы лежат блоками, а не одним массивом.

## const и reverse итераторы

Обычный итератор позволяет менять элемент, если контейнер не `const`.

```cpp
std::vector<int> values{1, 2, 3};

auto it = values.begin();
*it = 10;
```

`const_iterator` дает доступ только для чтения.

```cpp
auto it = values.cbegin();

// *it = 10; // ошибка
```

Важно: `const auto it = values.begin()` - это не const iterator.

```cpp
const auto it = values.begin();

*it = 10; // ok, элемент можно менять
// ++it;  // ошибка, сама переменная it const
```

Константность переменной-итератора и константность элемента - разные вещи.

Для обратного обхода есть:

- `rbegin()`;
- `rend()`;
- `crbegin()`;
- `crend()`.

```cpp
for (auto it = values.rbegin(); it != values.rend(); ++it) {
    std::cout << *it << ' ';
}
```

## Range-based for

Range-based for внутри тоже работает через `begin()` и `end()`.

```cpp
std::vector<int> values{1, 2, 3};

for (int value : values) {
    std::cout << value << ' ';
}
```

Упрощенно компилятор превращает это в цикл с итераторами:

```cpp
auto&& range = values;
auto begin = range.begin();
auto end = range.end();

for (; begin != end; ++begin) {
    int value = *begin;
}
```

По умолчанию `auto value` копирует элемент.

Для тяжелых объектов лучше использовать ссылку.

```cpp
for (const auto& value : values) {
    // читаем без копирования
}
```

Для изменения элементов нужна изменяемая ссылка.

```cpp
for (auto& value : values) {
    value += 1;
}
```

## std::next, std::prev, std::advance

`std::next` возвращает новый итератор, сдвинутый вперед.

```cpp
std::vector<int> values{1, 2, 3};

auto it = std::next(values.begin(), 2);
```

Для random access iterator это `O(1)`.

Для `std::list` или `std::forward_list` это может быть `O(N)`.

`std::prev` двигает назад и требует bidirectional iterator.

```cpp
std::list<int> values{1, 2, 3};

auto it = std::prev(values.end());
```

`std::advance` двигает сам переданный итератор.

```cpp
auto it = values.begin();
std::advance(it, 2);
```

## std::distance

`std::distance` считает расстояние между двумя итераторами.

```cpp
std::vector<int> v{1, 2, 3};
std::list<int> l{1, 2, 3};

auto a = std::distance(v.begin(), v.end()); // O(1)
auto b = std::distance(l.begin(), l.end()); // O(N)
```

Функция выбирает эффективный способ по категории итератора.

У random access iterator есть вычитание.

У list нужно пройти элементы один за другим.

## Концепты итераторов

В C++20 можно явно ограничивать алгоритмы категорией итератора.

```cpp
template <std::forward_iterator It>
std::size_t count_equal_neighbors(It first, It last) {
    if (first == last) {
        return 0;
    }

    std::size_t count = 0;
    auto prev = first;
    ++first;

    while (first != last) {
        if (*prev == *first) {
            ++count;
        }
        prev = first;
        ++first;
    }

    return count;
}
```

Для алгоритмов, где нужен `it + n`, требуется `std::random_access_iterator`.

```cpp
template <std::random_access_iterator It>
It middle(It first, It last) {
    return first + std::distance(first, last) / 2;
}
```

Такой код не примет `std::list::iterator`, потому что у него нет произвольного доступа.

## Алгоритм через итераторы

Плохой универсальный поиск через индексы:

```cpp
template <class Container, class T>
bool contains(const Container& c, const T& value) {
    for (std::size_t i = 0; i < c.size(); ++i) {
        if (c[i] == value) {
            return true;
        }
    }
    return false;
}
```

Он не работает для `std::list`.

Лучше принимать пару итераторов.

```cpp
template <class It, class T>
It find_value(It first, It last, const T& value) {
    while (first != last) {
        if (*first == value) {
            return first;
        }
        ++first;
    }

    return last;
}
```

Такой алгоритм работает с любым forward/input диапазоном.

## Подводные камни

## 1. end() нельзя разыменовывать

```cpp
auto it = values.end();

// std::cout << *it; // undefined behavior
```

`end()` - это не последний элемент.

## 2. begin() пустого контейнера тоже нельзя разыменовывать

```cpp
std::vector<int> values;

auto it = values.begin();

// *it; // undefined behavior, потому что begin() == end()
```

Сначала проверь `it != values.end()`.

## 3. Не все итераторы умеют одно и то же

```cpp
std::list<int> values{1, 2, 3};
auto it = values.begin();

// it + 1; // ошибка
```

Для универсального кода используй `std::next`, `std::advance` и стандартные алгоритмы.

## 4. Random access не значит contiguous

```cpp
std::deque<int> values{1, 2, 3};
```

У `deque` есть `it + n`, но нет одного непрерывного массива всех элементов.

В C-like API можно передавать только contiguous диапазоны.

## 5. iterator и const_iterator - разные типы

```cpp
std::vector<int>::iterator it;
std::vector<int>::const_iterator cit;
```

Первый может менять элемент, второй - нет.

## 6. for-range может копировать тяжелые объекты

```cpp
for (auto value : values) {
    // value - копия
}
```

Если копия дорогая, используй `const auto&`.

## 7. distance не всегда O(1)

```cpp
std::distance(values.begin(), values.end());
```

Для `std::vector` это `O(1)`.

Для `std::list` это `O(N)`.

## 8. Концепт должен соответствовать алгоритму

Если алгоритм использует `it + n`, ему нужен `std::random_access_iterator`.

Если алгоритм только читает и делает `++it`, достаточно input или forward iterator.

## Саммари

- Итератор обобщает указатель на элемент.
- Итераторы позволяют писать алгоритмы независимо от контейнера.
- `begin()` - первый элемент.
- `end()` - позиция после последнего.
- `end()` нельзя разыменовывать.
- Минимально итератору нужны `*`, `++` и сравнение.
- `operator->` дает доступ к полям и методам объекта.
- Input iterator читает последовательность один раз.
- Forward iterator идет вперед и допускает многократный проход.
- Bidirectional iterator умеет `--`.
- Random access iterator умеет `+ n`, `- n` и разность итераторов.
- Contiguous iterator означает непрерывную память.
- `std::deque` - random access, но не contiguous.
- `cbegin/cend` дают константные итераторы.
- `rbegin/rend` дают обратный обход.
- `const auto it = begin()` делает const сам итератор, а не элемент.
- Range-based for разворачивается в цикл через `begin()` и `end()`.
- `auto` в for-range копирует элемент, `auto&` и `const auto&` работают со ссылкой.
- `std::next`, `std::prev`, `std::advance` обобщают сдвиг итераторов.
- `std::distance` может быть `O(1)` или `O(N)` в зависимости от категории.
- C++20-концепты позволяют требовать `std::forward_iterator`, `std::random_access_iterator` и другие категории.
