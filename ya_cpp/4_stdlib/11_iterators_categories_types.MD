# 11. Итераторы: категории, свойства и типы

## Суть

Итератор - объект, который указывает на элемент контейнера и умеет двигаться по последовательности.

Он похож на обобщенный указатель.

```cpp
auto it = values.begin();
```

## Пример 1: begin/end

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

`begin()` указывает на первый элемент.

`end()` указывает на позицию после последнего элемента.

## Пример 2: const_iterator

```cpp
void print(const std::vector<int>& values) {
    for (auto it = values.cbegin(); it != values.cend(); ++it) {
        std::cout << *it << ' ';
    }
}
```

Через `const_iterator` нельзя менять элементы.

## Категории итераторов

- input iterator - читать вперед;
- forward iterator - проходить вперед много раз;
- bidirectional iterator - идти вперед и назад;
- random access iterator - прыгать по индексам;
- contiguous iterator - элементы лежат подряд в памяти.

## Пример 3: random access

```cpp
std::vector<int> values{10, 20, 30};

auto it = values.begin();
it += 2;

std::cout << *it << '\n';
```

Так умеют итераторы `std::vector` и `std::array`.

## Пример 4: list

```cpp
std::list<int> values{10, 20, 30};

auto it = values.begin();
++it;
--it;
```

У `std::list` итератор двунаправленный, но не random access.

```cpp
// it += 2; // ошибка
```

## Подводные камни

## 1. end() нельзя разыменовывать

```cpp
auto it = values.end();

// std::cout << *it; // ошибка
```

`end()` - это не последний элемент.

## 2. Не все итераторы умеют одно и то же

```cpp
std::list<int> values{1, 2, 3};
auto it = values.begin();

// it + 1; // ошибка
```

Для универсального кода нужны алгоритмы вроде `std::next`.

## 3. iterator и const_iterator - разные типы

```cpp
std::vector<int>::iterator it;
std::vector<int>::const_iterator cit;
```

Первый может менять элемент, второй - нет.

## Саммари

- Итератор обобщает указатель на элемент.
- `begin()` - первый элемент.
- `end()` - позиция после последнего.
- `end()` нельзя разыменовывать.
- Категория итератора определяет доступные операции.
- У `vector` итераторы сильнее, чем у `list`.
