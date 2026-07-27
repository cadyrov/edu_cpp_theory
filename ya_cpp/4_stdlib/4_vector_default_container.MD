# 4. Контейнер по умолчанию: std::vector

## Суть

`std::vector` - основной контейнер для последовательности элементов.

Он хранит элементы подряд в памяти и умеет автоматически расти.

```cpp
#include <vector>

std::vector<int> values;
```

Если нет причины выбрать другой контейнер, часто начинают с `std::vector`.

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

## Пример 2: доступ по индексу

```cpp
std::vector<int> values{10, 20, 30};

std::cout << values[0] << '\n';
std::cout << values.at(1) << '\n';
```

`operator[]` не проверяет границы.

`at()` проверяет и бросает исключение при ошибке.

## Пример 3: reserve

```cpp
std::vector<int> values;
values.reserve(100);

for (int i = 0; i < 100; ++i) {
    values.push_back(i);
}
```

`reserve` заранее выделяет память под элементы.

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

values[0] = 42; // ошибка: элемента еще нет
```

После `reserve` нужно использовать `push_back` или `resize`.

## 3. resize создает элементы

```cpp
std::vector<int> values;
values.resize(10);

values[0] = 42; // ok
```

`resize` меняет количество элементов.

## 4. Вставка в середину дорогая

```cpp
values.insert(values.begin(), 10);
```

Элементы после места вставки придется сдвигать.

## Саммари

- `std::vector` - контейнер по умолчанию для последовательностей.
- Элементы лежат подряд в памяти.
- `push_back` добавляет в конец.
- `reserve` меняет вместимость, но не размер.
- `resize` меняет размер.
- Доступ через `[]` не проверяет границы.
- Вставка и удаление в середине стоят дороже, чем работа с концом.
