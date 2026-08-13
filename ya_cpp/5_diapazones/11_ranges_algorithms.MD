# 11. Диапазонные формы алгоритмов

## Суть

`std::ranges` предоставляет современные версии стандартных алгоритмов:

```cpp
std::sort(values.begin(), values.end());
std::ranges::sort(values);
```

Ranges-алгоритмы:

- принимают диапазон целиком или пару `iterator + sentinel`;
- проверяют требования концептами;
- поддерживают проекции;
- часто возвращают несколько полезных итераторов;
- вызываются как функциональные объекты.

## Диапазон вместо двух итераторов

```cpp
std::vector<int> values{4, 1, 3, 2};

std::ranges::sort(values);
auto it = std::ranges::find(values, 3);
```

Для нестандартной границы можно передать итератор и sentinel разных типов:

```cpp
auto it = std::ranges::find(first, sentinel, value);
```

## Концепты

Требования алгоритма описываются явно. Например, сортировка требует диапазон произвольного доступа:

```cpp
std::vector<int> vector{3, 1, 2};
std::ranges::sort(vector); // корректно

std::list<int> list{3, 1, 2};
// std::ranges::sort(list); // не random_access_range
```

Ошибка возникает на уровне невыполненного ограничения, а не внутри реализации алгоритма.

## Проекции

```cpp
struct Connection {
    int id;
    bool busy;
};

std::vector<Connection> pool{
    {1, true}, {2, false}, {3, true}
};

auto free = std::ranges::find(pool, false, &Connection::busy);
```

Проекция позволяет искать по полю без отдельного предиката.

```cpp
std::ranges::sort(pool, {}, &Connection::id);
```

## Возвращаемые значения

Классический `std::copy` возвращает только конец выходного диапазона. Диапазонная форма возвращает оба достигнутых итератора:

```cpp
auto [inputEnd, outputEnd] = std::ranges::copy(
    source,
    destination.begin()
);
```

Подобные структуры обычно называются `in_out_result`, `in_in_result` и так далее.

## Новые алгоритмы C++23

```cpp
bool prefix = std::ranges::starts_with(values, beginning);
bool suffix = std::ranges::ends_with(values, ending);
bool hasValue = std::ranges::contains(values, 42);
bool hasPart = std::ranges::contains_subrange(values, part);
auto last = std::ranges::find_last(values, 42);
```

В C++23 диапазонные формы также получили `iota`, `shift_left` и `shift_right`.

## Свёртки

`fold_left` последовательно обновляет состояние слева направо:

```cpp
auto sum = std::ranges::fold_left(
    values,
    0,
    std::plus{}
);
```

Для `[a, b, c]` результат равен:

```text
f(f(f(init, a), b), c)
```

`fold_left_first` использует первый элемент вместо `init`. `fold_right` и `fold_right_last` сворачивают справа.

```cpp
auto count = std::ranges::fold_left(
    values,
    std::size_t{0},
    [target](std::size_t result, const auto& value) {
        return result + (value == target);
    }
);
```

## Подводные камни

### 1. У ranges-алгоритмов нет execution policy

В C++20/23 им нельзя передать `std::execution::par`, в отличие от ряда классических алгоритмов.

### 2. Алгоритмы не являются ленивыми

`std::ranges::sort`, `copy` и `fold_left` выполняются сразу. Ленивые цепочки создают адаптеры `std::views`.

### 3. Проверяй возвращаемый тип

Алгоритм над временным владеющим диапазоном может вернуть `std::ranges::dangling`.

### 4. Проекция может вызываться многократно

Она должна быть дешёвой и не зависеть от побочных эффектов.

### 5. Учитывай версию стандарта

`contains`, `find_last`, `fold_left` и другие перечисленные дополнения требуют C++23.

### 6. Правая свёртка требует более сильный диапазон

Для движения справа налево исходный диапазон должен поддерживать необходимые операции итератора.

## Саммари

- Ranges-алгоритмы принимают диапазоны и `iterator + sentinel`.
- Концепты проверяют требования в точке вызова.
- Проекции упрощают обработку полей объектов.
- Результат алгоритма может содержать несколько итераторов.
- C++23 добавил проверки наличия, поиск с конца и семейство `fold`.
- Ranges-алгоритмы выполняются сразу и не имеют параллельных форм в C++20/23.
