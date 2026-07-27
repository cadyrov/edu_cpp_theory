# 10. Невладеющие последовательности: std::string_view и std::span

## Суть

Невладеющая последовательность не хранит данные.

Она только смотрит на уже существующие данные.

В стандартной библиотеке часто используют:

- `std::string_view` - вид на строку;
- `std::span` - вид на массив элементов.

## std::string_view

```cpp
#include <iostream>
#include <string_view>

void print(std::string_view text) {
    std::cout << text << '\n';
}

int main() {
    print("hello");
}
```

`std::string_view` не копирует строку.

## std::span

```cpp
#include <iostream>
#include <span>
#include <vector>

void print(std::span<const int> values) {
    for (int value : values) {
        std::cout << value << ' ';
    }
}

int main() {
    std::vector<int> values{1, 2, 3};
    print(values);
}
```

`std::span` хранит указатель и размер.

## Пример 1: общий интерфейс

```cpp
void print(std::span<const int> values);

std::array<int, 3> a{1, 2, 3};
std::vector<int> v{4, 5, 6};

print(a);
print(v);
```

Одна функция может принять разные контейнеры с непрерывной памятью.

## Пример 2: подвид

```cpp
std::string_view text = "abcdef";
std::string_view part = text.substr(1, 3);
```

`part` смотрит на `"bcd"` без копирования символов.

## Подводные камни

## 1. Висячий string_view

```cpp
std::string_view bad() {
    std::string s = "hello";
    return s; // ошибка: view на уничтоженную строку
}
```

`string_view` не продлевает жизнь строки.

## 2. string_view не обязан быть null-terminated

```cpp
std::string_view text{"abc\0def", 7};
```

Нельзя бездумно передавать `text.data()` в C API, ожидающий `'\0'`.

## 3. span требует непрерывную память

```cpp
std::list<int> values{1, 2, 3};

// std::span<int> s = values; // ошибка
```

`std::list` не подходит.

## 4. span тоже не владеет данными

```cpp
std::span<int> make_bad() {
    std::vector<int> values{1, 2, 3};
    return values; // ошибка: span на уничтоженный vector
}
```

Данные должны жить дольше, чем view.

## Саммари

- `std::string_view` и `std::span` не владеют данными.
- Они дешевы для передачи в функции.
- `string_view` удобен для чтения строк без копии.
- `span` удобен для массивов и векторов.
- Главный риск - висячий view.
- `span` работает только с непрерывной памятью.
