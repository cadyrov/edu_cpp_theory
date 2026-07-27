# 4. Контейнер по умолчанию: std::vector

## Суть

`std::vector` - основной контейнер для последовательности элементов с изменяемым размером.

Он владеет динамической памятью, хранит элементы непрерывно и умеет автоматически расти.

`std::vector` умеет менять и размер, и вместимость во время выполнения программы.

```cpp
#include <vector>

std::vector<int> values;
```

Если нет причины выбрать другой контейнер, часто начинают с `std::vector`.

## Устройство

Упрощенно `vector` можно представить так:

```cpp
template <class T>
class Vector {
    T* data_;
    std::size_t size_;
    std::size_t capacity_;
};
```

- `data_` - указатель на непрерывную память;
- `size_` - сколько элементов реально создано;
- `capacity_` - сколько элементов можно хранить без новой аллокации.

Пустой `vector` обычно имеет `size() == 0`, `capacity() == 0`, `data() == nullptr`.

Когда при добавлении места не хватает, происходит реаллокация:

1. выделяется новый буфер большего размера;
2. старые элементы копируются или перемещаются;
3. новый элемент добавляется;
4. старая память освобождается.

Обычно новая вместимость берется с запасом, чтобы не делать реаллокацию на каждый `push_back`.

## Создание

```cpp
std::vector v = {1, 2, 3};
```

Через CTAD тип будет `std::vector<int>`.

```cpp
std::vector<int> a(3);     // 3 элемента: 0 0 0
std::vector<int> b(3, 10); // 3 элемента: 10 10 10
std::vector<int> c{3, 10}; // 2 элемента: 3 10
```

Круглые и фигурные скобки здесь имеют разный смысл.

## Пример 1: добавление

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> values;

    values.push_back(10);
    values.push_back(20);
    values.push_back(30);

    for (int value : values) {
        std::cout << value << ' ';
    }
}
```

`push_back` добавляет элемент в конец.

## push_back и emplace_back

```cpp
struct Player {
    explicit Player(int number) {}
};

std::vector<Player> players;

players.emplace_back(1);
players.push_back(Player{2});
```

`emplace_back` создает элемент сразу внутри вектора.

`push_back` принимает уже готовый объект и копирует или перемещает его в вектор.

## Доступ по индексу

```cpp
std::vector<int> values{10, 20, 30};

std::cout << values[0] << '\n';
std::cout << values.at(1) << '\n';
```

`operator[]` не проверяет границы.

`at()` проверяет и бросает `std::out_of_range`.

Можно получить ссылку на элемент:

```cpp
int& x = values[1];
x *= 2;
```

У `const std::vector` доступ возвращает только `const`-ссылку.

## reserve и resize

```cpp
std::vector<int> values;
values.reserve(100);
```

`reserve` заранее выделяет память, но не создает элементы.

```cpp
std::vector<int> values;
values.reserve(10);

// values[0] = 42; // undefined behavior
```

Чтобы создать элементы, нужен `resize`.

```cpp
std::vector<int> values;
values.resize(10);

values[0] = 42; // ok
```

`resize` меняет количество элементов.

## shrink_to_fit

Удаление элементов не обязано уменьшать `capacity()`.

```cpp
std::vector<int> values;
values.reserve(100);
values.resize(10);

values.shrink_to_fit();
```

`shrink_to_fit` просит контейнер уменьшить вместимость.

Это может привести к новой аллокации и переносу элементов.

## noexcept move при реаллокации

При реаллокации `vector` должен перенести старые элементы в новый буфер.

Если move constructor типа `T` помечен как `noexcept`, `vector` может перемещать элементы.

Если move может бросить исключение, `vector` часто выбирает копирование, чтобы сохранить строгую гарантию исключений.

```cpp
struct X {
    X(const X&) {}
    X(X&&) noexcept {}
};
```

Для типов, которые планируется хранить в `std::vector`, полезно делать move constructor `noexcept`, если это корректно.

## Удаление

```cpp
std::vector<int> values{1, 2, 3};

values.pop_back();
```

`pop_back` удаляет последний элемент.

Память обычно не освобождается, уменьшается только `size()`.

Для удаления по условию часто используют erase-remove:

```cpp
std::vector<int> values{1, 2, 3, 4, 5};

auto it = std::remove_if(values.begin(), values.end(), [](int x) {
    return x % 2 == 0;
});

values.erase(it, values.end());
```

`remove_if` переставляет элементы и возвращает новый логический конец.

`erase` реально удаляет хвост.

## Алгоритмы

`std::vector` хорошо работает со стандартными алгоритмами.

```cpp
std::vector<int> values{1, 2, 3};

std::transform(values.begin(), values.end(), values.begin(), [](int x) {
    return x * x;
});
```

```cpp
std::vector<int> values{4, 3, 2, 1};

std::sort(values.begin(), values.end());

auto it = std::lower_bound(values.begin(), values.end(), 3);
```

После сортировки можно использовать бинарный поиск.

Для задач приоритета можно построить кучу:

```cpp
std::vector<int> values{3, 2, 4, 1, 5, 9};

std::make_heap(values.begin(), values.end());
```

После `make_heap` максимальный элемент будет в `values.front()`.

## C API

Так как элементы лежат непрерывно, `vector` можно передавать в C-style API через `data()` и `size()`.

```cpp
void api(char* data, std::size_t size);

std::vector<char> buffer{'h', 'e', 'l', 'l', 'o'};

api(buffer.data(), buffer.size());
```

`data()` возвращает указатель на первый элемент массива.

`size()` возвращает количество созданных элементов.

Такой интерфейс удобен для C-like-функций, которые принимают указатель и размер.

## std::vector<bool>

`std::vector<bool>` - особенная специализация.

Обычный `std::vector<T>` хранит каждый элемент как отдельный объект `T`.

`std::vector<bool>` может упаковывать несколько булевых значений в один машинный блок.

```cpp
std::vector<bool> flags{true, false, true};
```

Из-за упаковки элемент `flags[0]` - не настоящий `bool&`, а специальный proxy-объект.

```cpp
auto x = flags[0]; // proxy, а не обычная ссылка bool&
```

Это экономит память, но может ломать ожидания в generic-коде.

Если нужен обычный массив байтовых флагов, часто проще взять:

```cpp
std::vector<char> flags;
```

## Подводные камни

## 1. size и capacity

```cpp
std::vector<int> values;
values.reserve(10);

values.size();     // 0
values.capacity(); // минимум 10
```

`size` - сколько элементов есть.

`capacity` - сколько можно положить без нового выделения памяти.

## 2. reserve не создает элементы

```cpp
std::vector<int> values;
values.reserve(10);

values[0] = 42; // undefined behavior
```

После `reserve` нужно использовать `push_back` или `resize`.

## 3. resize требует default constructible

```cpp
struct User {
    explicit User(int id) {}
};

std::vector<User> users;

// users.resize(10); // ошибка
```

При расширении `resize` должен создать новые элементы.

Если конструктора по умолчанию нет, добавляй через `emplace_back`.

## 4. at() и operator[]

```cpp
std::vector<int> values{1, 2, 3};

values[10] = 5;    // undefined behavior
values.at(10) = 5; // std::out_of_range
```

`[]` быстрее, но не проверяет границы.

## 5. Реаллокация инвалидирует указатели

```cpp
std::vector<int> values{1, 2, 3};
int* p = values.data();

values.push_back(4); // может быть реаллокация

// p может стать невалидным
```

После роста буфер может переехать.

## 6. shrink_to_fit не гарантия

```cpp
values.shrink_to_fit();
```

Это просьба уменьшить вместимость, а не жесткое требование.

## 7. make_heap не сортирует

`std::make_heap` перестраивает диапазон в кучу.

Это не то же самое, что `std::sort`.

## Саммари

- `std::vector` - контейнер по умолчанию для последовательностей.
- Он владеет динамической памятью.
- Элементы лежат непрерывно.
- В основе `std::vector` лежит динамический массив.
- К элементам можно обращаться через арифметику указателей.
- `size()` - число созданных элементов.
- `capacity()` - вместимость без новой аллокации.
- Размер и вместимость могут меняться во время выполнения.
- При нехватке места `vector` делает реаллокацию с запасом.
- `reserve` меняет вместимость, но не создает элементы.
- `resize` меняет размер и создает или удаляет элементы.
- `push_back` добавляет готовый объект.
- `emplace_back` создает объект сразу внутри вектора.
- `operator[]` не проверяет границы.
- `at()` проверяет границы и бросает `std::out_of_range`.
- `pop_back` удаляет последний элемент, но обычно не уменьшает `capacity()`.
- Для удаления по условию используют erase-remove.
- `vector` удобно передавать в C API через `data()` и `size()`.
- `std::vector<bool>` - специальная упакованная версия с proxy-объектами вместо обычных `bool&`.
- Для пользовательских типов полезен `noexcept` move constructor.
