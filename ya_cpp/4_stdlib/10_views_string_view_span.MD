# 10. Невладеющие последовательности: std::string_view и std::span

## Суть

Невладеющая последовательность не хранит данные.

Она только смотрит на уже существующие данные.

В стандартной библиотеке часто используют:

- `std::string_view` - вид на строку;
- `std::span` - вид на массив элементов.

Главное правило: данные должны жить дольше, чем view.

## std::string_view

`std::string_view` - легкий объект для чтения строки без владения.

Обычно он хранит два поля:

- указатель на начало;
- размер.

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

`std::string_view` удобно передавать в функцию по значению.

Копируется только указатель и размер, а не символы.

## Что можно передать в string_view

```cpp
void print(std::string_view text);

std::string s = "Hello";
const char* c = "World";

print(s);
print(c);
print({c, 3}); // "Wor"
```

`std::string_view` можно создать из:

- `std::string`;
- C-строки;
- пары `const char*` + размер.

## Зачем он нужен

Если функция принимает `const std::string&`, строковый литерал сначала может превратиться во временный `std::string`.

```cpp
void log(const std::string& text);

log("hello"); // может создаться временный std::string
```

Если функция принимает `std::string_view`, копировать текст не нужно.

```cpp
void log(std::string_view text);

log("hello"); // view на литерал
```

Используй `std::string_view`, когда функция только читает строку.

## remove_prefix и remove_suffix

`std::string_view` не может менять исходную строку.

Но он может менять собственные границы.

```cpp
std::string_view text = "Hello World!";

text.remove_prefix(6);
text.remove_suffix(1);
```

Теперь `text` смотрит на `"World"`.

Исходные символы не менялись.

## substr без копии

```cpp
std::string_view text = "abcdef";
std::string_view part = text.substr(1, 3);
```

`part` смотрит на `"bcd"` без копирования символов.

Это отличие от `std::string::substr`, который создает новую строку.

## Строковые константы

Для строковых констант `std::string_view` часто удобнее, чем `const char*` и `const char[]`.

```cpp
const std::string_view content_type = "application/json";

std::cout << content_type.size() << '\n';
```

У `const char*` `sizeof` даст размер указателя.

У `const char[]` `sizeof` даст размер массива вместе с `'\0'`.

У `std::string_view` есть явный `size()` без учета завершающего нуля.

Можно использовать литерал `sv`.

```cpp
using namespace std::string_view_literals;

const auto content_type = "application/json"sv;
```

## C API

`std::string_view` не обязан заканчиваться `'\0'`.

```cpp
std::string s = "123";
std::string_view sv{s.data(), 1};

// std::strlen(sv.data()); // прочитает не только view
```

Если C API ждет null-terminated строку, используй `std::string` и `c_str()`.

```cpp
std::string s = "123";
std::strlen(s.c_str()); // ok
```

## std::span

`std::span` - невладеющий вид на непрерывный массив элементов.

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

Одна функция может принять разные контейнеры с непрерывной памятью.

```cpp
void print(std::span<const int> values);

std::array<int, 3> a{1, 2, 3};
std::vector<int> v{4, 5, 6};

print(a);
print(v);
```

## Подводные камни

## 1. Висячий string_view

```cpp
std::string_view bad() {
    std::string s = "hello";
    return s; // view на уничтоженную строку
}
```

`string_view` не продлевает жизнь строки.

## 2. Опасный substr

```cpp
std::string_view find_name(const std::string& text) {
    auto pos = text.find(", ");
    return text.substr(pos + 2); // ошибка: std::string::substr вернул временную строку
}
```

`std::string::substr` возвращает `std::string`.

Временная строка уничтожится, а `string_view` повиснет.

Лучше сначала создать view:

```cpp
std::string_view find_name(std::string_view text) {
    auto pos = text.find(", ");
    return text.substr(pos + 2);
}
```

## 3. string_view не обязан быть null-terminated

```cpp
std::string_view text{"abc\0def", 7};
```

Нельзя бездумно передавать `text.data()` в C API, ожидающий `'\0'`.

## 4. string_view не меняет символы

```cpp
std::string s = "Hello";
std::string_view view = s;

// view[0] = 'h'; // ошибка
```

`std::string_view` дает доступ только для чтения.

## 5. span требует непрерывную память

```cpp
std::list<int> values{1, 2, 3};

// std::span<int> s = values; // ошибка
```

`std::list` не подходит.

## 6. span тоже не владеет данными

```cpp
std::span<int> make_bad() {
    std::vector<int> values{1, 2, 3};
    return values; // span на уничтоженный vector
}
```

Данные должны жить дольше, чем view.

## Саммари

- `std::string_view` и `std::span` не владеют данными.
- Они дешевы для передачи в функции по значению.
- `std::string_view` хранит указатель и размер.
- `std::string_view` удобен для чтения строк без копии.
- Его можно создать из `std::string`, C-строки и указателя с размером.
- `remove_prefix` и `remove_suffix` меняют только сам view.
- `std::string_view::substr` не копирует символы.
- `std::string::substr` копирует и может создать временную строку.
- `std::string_view` не обязан заканчиваться `'\0'`.
- Для C API, ожидающего `'\0'`, нужен `std::string::c_str()`.
- Главный риск - висячий view.
- `std::span` удобен для массивов и векторов.
- `std::span` работает только с непрерывной памятью.
