# 8. Строки

## Суть

`std::string` - стандартная строка с владением.

Она хранит символы, управляет памятью и умеет менять размер.

```cpp
#include <string>

std::string name = "Alex";
```

## Пример 1: создание и склейка

```cpp
#include <iostream>
#include <string>

int main() {
    std::string first = "Hello";
    std::string second = "world";

    std::string text = first + ", " + second;

    std::cout << text << '\n';
}
```

Вывод:

```text
Hello, world
```

## Пример 2: изменение

```cpp
std::string s = "abc";

s.push_back('d');
s[0] = 'A';
```

Строка станет `"Abcd"`.

## Пример 3: подстрока

```cpp
std::string s = "abcdef";

std::string part = s.substr(1, 3);
```

`part` будет равен `"bcd"`.

## Пример 4: поиск

```cpp
std::string s = "hello world";

auto pos = s.find("world");
if (pos != std::string::npos) {
    std::cout << pos << '\n';
}
```

`npos` означает "не найдено".

## Подводные камни

## 1. char - не символ Unicode

```cpp
std::string s = "привет";
```

`std::string` хранит байты.

В UTF-8 один видимый символ может занимать несколько байт.

## 2. operator[] не проверяет границы

```cpp
std::string s = "abc";

char c = s[10]; // undefined behavior
```

Для проверки есть `at()`.

## 3. c_str() живет пока строка не изменилась

```cpp
std::string s = "abc";
const char* p = s.c_str();

s += "def";

// p может стать невалидным
```

Изменение строки может перевыделить буфер.

## 4. substr копирует

```cpp
std::string part = s.substr(0, 5);
```

Создается новая строка.

Если нужен только невладеющий вид, используют `std::string_view`.

## Саммари

- `std::string` владеет строковыми данными.
- Строку можно менять и расширять.
- `find` возвращает позицию или `std::string::npos`.
- `substr` создает копию.
- `std::string` хранит байты, а не абстрактные символы Unicode.
- Указатель из `c_str()` может стать невалидным после изменения строки.
