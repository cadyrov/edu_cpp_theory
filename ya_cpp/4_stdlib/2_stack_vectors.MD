# 2. Стековые векторы

## Суть

Стековый вектор - это контейнер с фиксированной вместимостью и изменяемым размером.

В стандартной библиотеке для этого есть `std::inplace_vector`.

```cpp
std::inplace_vector<int, 5> v = {1, 2, 3};
```

Вместимость `5` задается на этапе компиляции и не меняется во время работы программы.

Размер `v.size()` может меняться от `0` до `v.capacity()`.

Элементы лежат непрерывно в автоматической или статической памяти. Динамических аллокаций для хранения элементов нет.

## Зачем нужен inplace_vector

`std::array` всегда содержит ровно `N` элементов.

`std::inplace_vector` содержит до `N` элементов.

Это полезно, когда:

- нельзя или нежелательно использовать динамическую память;
- нужен буфер с верхней границей размера;
- элементы не имеют конструктора по умолчанию;
- время жизни элементов должно начинаться при добавлении.

```cpp
struct Object {
    explicit Object(int value) {}
};

std::inplace_vector<Object, 3> values;

values.emplace_back(1);
values.emplace_back(2);
```

Такой код работает, хотя `Object` нельзя создать без аргументов.

## Пример 1: добавление

```cpp
#include <inplace_vector>
#include <iostream>

int main() {
    std::inplace_vector<int, 5> values;

    values.push_back(10);
    values.push_back(20);
    values.emplace_back(30);

    for (int value : values) {
        std::cout << value << ' ';
    }
}
```

Вывод:

```text
10 20 30
```

## Пример 2: проверка вместимости

```cpp
std::inplace_vector<int, 2> values;

values.push_back(1);
values.push_back(2);

// values.push_back(3); // std::bad_alloc
```

Если места нет, обычный `push_back` бросает `std::bad_alloc`.

Для явной проверки можно использовать `try_push_back`.

```cpp
if (values.try_push_back(3) == nullptr) {
    std::cout << "no space\n";
}
```

## Пример 3: unchecked-добавление

```cpp
std::inplace_vector<int, 2> values;

values.unchecked_push_back(1);
values.unchecked_push_back(2);
```

`unchecked_push_back` не проверяет вместимость.

Если места нет, будет undefined behavior.

## Пример 4: C-style API

```cpp
void print(const int* data, std::size_t size);

std::inplace_vector<int, 4> values = {1, 2, 3};

print(values.data(), values.size());
```

Так можно передать непрерывные данные в функцию, ожидающую указатель и размер.

## Стоимость операций

- доступ по индексу - `O(1)`;
- `size()` - `O(1)`;
- добавление в конец - `O(1)`;
- удаление с конца - `O(1)`;
- вставка в середину - `O(N)`;
- удаление из середины - `O(N)`;
- `resize()` при расширении - `O(N)`;
- `std::sort` - `O(NlogN)`;
- `std::lower_bound` по отсортированному диапазону - `O(logN)`;
- `std::move` и `std::swap` - `O(N)`.

```cpp
std::inplace_vector<int, 4> values = {3, 1, 2};

std::sort(values.begin(), values.end());

auto it = std::lower_bound(values.begin(), values.end(), 2);
```

Итераторы поддерживают произвольный доступ, поэтому `std::sort` работает.

## Отличие move от array

У `std::array` после move размер не меняется: он всегда фиксирован.

У `std::inplace_vector` после move исходный контейнер остается валидным, но его состояние может быть неопределенным.

Для нетривиальных типов размер исходного контейнера после move не стоит угадывать.

```cpp
auto b = std::move(a);

std::cout << a.size(); // можно вызвать, но значение не надо предполагать
```

## Подводные камни

## 1. Вместимость не растет

```cpp
std::inplace_vector<int, 2> values;

values.push_back(1);
values.push_back(2);
values.push_back(3); // std::bad_alloc
```

Это не `std::vector`: реаллокации не будет.

## 2. try_push_back нужно проверять

```cpp
auto* p = values.try_push_back(42);

if (p == nullptr) {
    // элемент не добавлен
}
```

Игнорировать результат опасно.

## 3. unchecked_push_back требует доказанной вместимости

```cpp
values.unchecked_push_back(42);
```

Этот метод имеет смысл только там, где проверка уже сделана выше.

## 4. clear() уничтожает элементы

`clear()` удаляет все существующие элементы.

Для нетривиальных типов это не бесплатная операция.

## 5. Не везде доступен

`std::inplace_vector` - новый контейнер стандартной библиотеки.

Если его нет в используемой версии C++, похожую идею реализуют вручную или берут из библиотек.

## Когда что использовать

- `std::array` - всегда ровно `N` элементов.
- `std::inplace_vector` - до `N` элементов без динамической памяти.
- `std::vector` - размер может расти без заранее заданного верхнего лимита.

## Саммари

- `std::inplace_vector` хранит элементы непрерывно.
- Память под элементы находится внутри самого контейнера.
- Динамических аллокаций для хранения элементов нет.
- Вместимость фиксирована на этапе компиляции.
- Размер меняется во время выполнения от `0` до `capacity()`.
- В отличие от `std::array`, элементы можно добавлять и удалять.
- В отличие от `std::array`, тип элемента не обязан иметь конструктор по умолчанию для пустого контейнера.
- `push_back` при переполнении бросает `std::bad_alloc`.
- `try_push_back` возвращает `nullptr`, если места нет.
- `unchecked_push_back` дает undefined behavior при переполнении.
- Доступ по индексу и добавление в конец стоят `O(1)`.
- Вставка и удаление в середине стоят `O(N)`.
- `std::move` и `std::swap` стоят `O(N)`.
