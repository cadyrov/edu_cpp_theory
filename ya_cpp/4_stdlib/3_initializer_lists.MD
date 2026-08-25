# 3. Списки инициализации

## Суть

Список инициализации задается фигурными скобками.

```cpp
int x{10};
std::vector<int> values{1, 2, 3};
```

`std::initializer_list<T>` - легкий proxy-объект, который смотрит на массив константных элементов типа `T`.

Он не владеет обычным контейнером и не копирует элементы при копировании самого `initializer_list`.

## Зачем нужен initializer_list

Списки инициализации решают три частые задачи:

- единая инициализация объектов через `{}`;
- запрет сужающих преобразований;
- удобная инициализация контейнеров из фиксированного набора значений.

```cpp
int x{3.14}; // ошибка: narrowing conversion

std::vector<int> values{1, 2, 3};
std::map<std::string, int> ids{{"Ann", 1}, {"Bob", 2}};
```

## Пример 1: простые значения

```cpp
int a{10};
double b{3.14};
std::string s{"hello"};
```

Фигурные скобки запрещают опасное сужение типа.

```cpp
int x{3.14}; // ошибка
```

## Пример 2: контейнер

```cpp
#include <vector>

int main() {
    std::vector<int> values{1, 2, 3, 4};
}
```

Создается вектор из четырех элементов.

## Пример 3: std::initializer_list

```cpp
#include <initializer_list>
#include <iostream>

void print(std::initializer_list<int> values) {
    for (int value : values) {
        std::cout << value << ' ';
    }
}

int main() {
    print({10, 20, 30});
}
```

`std::initializer_list` обычно передают по значению.

Копируется только маленький proxy-объект, а не все элементы.

## Пример 4: методы

```cpp
std::initializer_list<int> values = {1, 2, 3};

std::cout << values.size() << '\n';

for (auto it = values.begin(); it != values.end(); ++it) {
    std::cout << *it << ' ';
}
```

У `initializer_list` есть `begin()`, `end()` и `size()`.

Его можно использовать в range-based for.

## Пример 5: auto

```cpp
auto words = {"hello", "world"};
```

Тип будет `std::initializer_list<const char*>`.

Все элементы списка должны приводиться к одному типу.

## Пример 6: конструктор класса

```cpp
#include <initializer_list>
#include <vector>

class Point {
public:
    Point(std::initializer_list<int> coordinates)
        : coordinates_(coordinates) {}

private:
    std::vector<int> coordinates_;
};

Point p1{1};
Point p2{1, 2};
Point p3{1, 2, 3};
```

Так можно принимать разное количество заранее заданных значений без вариадического шаблона.

## Подводные камни

## 1. vector: размер или элементы

```cpp
std::vector<int> a(3, 10); // 3 элемента со значением 10
std::vector<int> b{3, 10}; // 2 элемента: 3 и 10
```

Круглые и фигурные скобки здесь дают разный результат.

## 2. initializer_list часто выигрывает перегрузку

```cpp
struct X {
    X(int, int) {}
    X(std::initializer_list<int>) {}
};

X x{1, 2}; // выберется initializer_list
```

Фигурные скобки могут выбрать не тот конструктор, который ожидался.

## 3. Элементы initializer_list доступны только для чтения

```cpp
void foo(std::initializer_list<int> values) {
    for (const int& value : values) {
        // value менять нельзя
    }
}
```

Элементы списка считаются `const`.

## 4. Размер нельзя менять

```cpp
std::initializer_list<int> values = {1, 2, 3};

// values.push_back(4); // такого метода нет
```

Это view на фиксированный набор элементов.

## 5. Не стоит хранить initializer_list как долгоживущее состояние

```cpp
struct Bad {
    std::initializer_list<int> values;
};

Bad b{{1, 2, 3}}; // опасная идея
```

`initializer_list` не владеет данными как `std::vector`.

Для хранения скопируй элементы в контейнер.

## 6. Элементы должны быть одного типа

```cpp
auto values = {1, 2, 3}; // ok

// auto bad = {1, 2.5}; // ошибка вывода типа
```

Список должен иметь общий тип элементов.

## Саммари

- Фигурные скобки задают list initialization.
- `std::initializer_list<T>` смотрит на массив `const T`.
- У него есть `begin()`, `end()` и `size()`.
- Его удобно использовать в range-based for.
- `std::initializer_list` обычно передают по значению.
- Копирование `initializer_list` не копирует сами элементы.
- Он удобен для инициализации контейнеров и классов из фиксированного набора значений.
- Фигурные скобки запрещают сужающие преобразования.
- `std::vector<int>(3, 10)` и `std::vector<int>{3, 10}` - разные вещи.
- Элементы `initializer_list` нельзя менять.
- Размер списка нельзя менять.
- Для долгого хранения данных лучше копировать элементы в обычный контейнер.
