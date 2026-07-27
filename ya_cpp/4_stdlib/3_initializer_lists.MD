# 3. Списки инициализации

## Суть

Список инициализации задается фигурными скобками.

```cpp
int x{10};
std::vector<int> values{1, 2, 3};
```

Он удобен для создания объектов и контейнеров.

## Пример 1: простые значения

```cpp
int a{10};
double b{3.14};
std::string s{"hello"};
```

Такая форма запрещает опасные сужающие преобразования.

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

`std::initializer_list` принимает временный список значений.

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

## Саммари

- Фигурные скобки задают list initialization.
- Они удобны для контейнеров и объектов.
- Они запрещают сужающие преобразования.
- `std::vector<int>(3, 10)` и `std::vector<int>{3, 10}` - разные вещи.
- `std::initializer_list` может влиять на выбор конструктора.
