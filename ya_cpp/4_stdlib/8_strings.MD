# 8. Строки

## Суть

`std::string` - стандартная строка с владением.

Она хранит байты, управляет памятью, умеет менять размер и совместима с C-строками.

```cpp
#include <string>

std::string name = "Alex";
```

## C-строки

C-строка - это массив `char`, который заканчивается символом `'\0'`.

```cpp
char s[] = "Hello";
```

Здесь в массиве `6` байт:

- `H`;
- `e`;
- `l`;
- `l`;
- `o`;
- `'\0'`.

Пустая C-строка тоже содержит `'\0'`.

```cpp
char empty[] = "";
```

Если `'\0'` нет, функции вроде `strlen` будут читать память дальше и получат undefined behavior.

```cpp
char bad[3] = {'a', 'b', 'c'};

// std::strlen(bad); // undefined behavior
```

## Функции C-строк

```cpp
#include <cstring>

char s[] = "Hello";

std::strlen(s); // 5, без учета '\0'
```

Частые функции:

- `std::strlen` - длина до `'\0'`;
- `std::strcmp` - сравнение;
- `std::strcpy` - копирование.

Главный риск C-строк: программист сам следит за размером буфера и завершающим `'\0'`.

## std::string

`std::string` владеет памятью.

Он сам выделяет, освобождает и расширяет буфер.

```cpp
std::string s1;
std::string s2 = "Hello";
std::string s3(5, 'a'); // "aaaaa"
```

Когда строка уничтожается, ее память освобождается автоматически.

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

## Методы контейнера

У `std::string` есть методы, похожие на методы `std::vector`.

```cpp
std::string s = "Hello";

s.size();
s.empty();
s.reserve(100);
s.resize(3);
```

`reserve` меняет вместимость, но не размер.

`resize` меняет размер строки.

```cpp
std::string s = "Hello";

s.reserve(100);
s.resize(4); // "Hell"
```

`operator[]` не проверяет границы.

`at()` проверяет и бросает `std::out_of_range`.

```cpp
std::string s = "abc";

s[0] = 'A';
s.at(1) = 'B';
```

## Итераторы и алгоритмы

`std::string` поддерживает итераторы.

```cpp
std::string s = "bca";

std::sort(s.begin(), s.end());
```

После сортировки строка станет `"abc"`.

Можно искать символы:

```cpp
std::string s = "Hello World";

auto it = std::find(s.begin(), s.end(), ' ');
```

Можно преобразовывать:

```cpp
std::string s = "Hello World";

std::transform(s.begin(), s.end(), s.begin(), [](char c) {
    return c == ' ' ? '+' : c;
});
```

Строка станет `"Hello+World"`.

## Методы для текста

```cpp
std::string s = "Hello World";

auto pos = s.find("World");
```

`find` возвращает позицию или `std::string::npos`.

```cpp
std::string part = s.substr(6);
```

`part` будет равен `"World"`.

```cpp
bool ok = s.starts_with("Hello");
```

`starts_with` проверяет префикс.

```cpp
int cmp = std::string("abc").compare("bcd");
```

`compare` делает лексикографическое сравнение.

## Совместимость с C API

`std::string` можно создать из C-строки.

```cpp
std::string s = "Hello";
```

Метод `c_str()` возвращает указатель на C-строку с завершающим `'\0'`.

```cpp
std::string s = "Hello";

const char* p = s.c_str();
```

Гарантируется, что по адресу `s.c_str() + s.size()` лежит `'\0'`.

```cpp
assert(*(s.c_str() + s.size()) == '\0');
```

Для C API, которое принимает указатель и размер, можно использовать `data()` и `size()`.

```cpp
void api(const char* data, std::size_t size);

std::string s = "Hello";

api(s.data(), s.size());
```

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

## 5. C-функции ждут '\0'

```cpp
std::string s = "abc\0def";
```

Внутри `std::string` может быть `'\0'`.

C-функция, которая читает до `'\0'`, увидит только `"abc"`.

## Саммари

- C-строка - массив `char`, заканчивающийся `'\0'`.
- Без `'\0'` функции C-строк могут уйти за границы массива.
- `std::strlen` считает байты до `'\0'`.
- `std::string` владеет строковыми данными.
- Строку можно менять и расширять.
- У `std::string` есть `size()`, `empty()`, `reserve()`, `resize()`, `begin()`, `end()`.
- `operator[]` не проверяет границы.
- `at()` проверяет границы и бросает `std::out_of_range`.
- `find` возвращает позицию или `std::string::npos`.
- `substr` создает копию.
- `starts_with` проверяет префикс.
- `c_str()` возвращает C-строку с завершающим `'\0'`.
- Указатель из `c_str()` может стать невалидным после изменения строки.
- `std::string` хранит байты, а не абстрактные символы Unicode.
