# 10. Невладеющие последовательности: std::string_view, std::span, std::mdspan

## Суть

Невладеющая последовательность не хранит данные.

Она только смотрит на уже существующую память.

В стандартной библиотеке есть:

- `std::string_view` - вид на строку;
- `std::span` - вид на одномерный массив;
- `std::mdspan` - вид на многомерный массив.

Главное правило: исходные данные должны жить дольше, чем view.

## std::string_view

`std::string_view` хранит указатель на символы и размер.

```cpp
#include <string_view>

void log(std::string_view text);

std::string s = "hello";
const char* c = "world";

log(s);
log(c);
log("literal");
```

Его удобно передавать по значению: копируются только указатель и размер, а не символы.

## string_view и подстроки

`std::string_view` может менять свои границы, не меняя исходную строку.

```cpp
std::string_view text = "Hello World!";

text.remove_prefix(6);
text.remove_suffix(1);
```

Теперь `text` смотрит на `"World"`.

```cpp
std::string_view part = text.substr(1, 3);
```

`std::string_view::substr` не копирует символы.

`std::string::substr` копирует и возвращает новую строку.

## string_view и C API

`std::string_view` не обязан заканчиваться `'\0'`.

```cpp
std::string s = "123";
std::string_view sv{s.data(), 1};

// std::strlen(sv.data()); // прочитает больше, чем один символ
```

Если C API ждет C-строку, используй `std::string::c_str()`.

## Строковые константы

```cpp
const std::string_view content_type = "application/json";
```

Так проще получить корректный размер:

```cpp
content_type.size(); // 16
```

Можно использовать литерал `sv`.

```cpp
using namespace std::string_view_literals;

const auto content_type = "application/json"sv;
```

## std::span

`std::span<T>` - невладеющий вид на непрерывный массив элементов.

Он хранит указатель и размер.

```cpp
#include <span>
#include <vector>

void square_all(std::span<int> values) {
    for (int& value : values) {
        value *= value;
    }
}

int main() {
    std::vector<int> values{1, 2, 3};
    square_all(values);
}
```

Через `std::span<int>` можно менять исходные элементы.

Для чтения используй `std::span<const int>`.

```cpp
void print(std::span<const int> values);
```

`std::span` можно создать из:

- C-style массива;
- `std::array`;
- `std::vector`;
- указателя и размера.

```cpp
int raw[] = {1, 2, 3};
std::array<int, 3> arr{1, 2, 3};
std::vector<int> vec{1, 2, 3};

print(raw);
print(arr);
print(vec);
print({vec.data(), 2});
```

## span и C API

`std::span` удобно использовать между C++-кодом и C-like API.

```cpp
void api(int* data, std::size_t size);

std::vector<int> values{1, 2, 3};
std::span<int> view = values;

api(view.data(), view.size());
```

В отличие от C-style массива, `span` не теряет размер при передаче в функцию.

## Subspan

У `std::span` есть методы для создания view на часть диапазона:

- `first(count)`;
- `last(count)`;
- `subspan(offset, count)`.

```cpp
std::array<int, 5> values{1, 2, 3, 4, 5};
std::span<int> s = values;

auto first = s.first(3);      // 1 2 3
auto last = s.last(2);        // 4 5
auto middle = s.subspan(1, 3); // 2 3 4
```

Данные не копируются.

## Статический и динамический extent

У `std::span` размер может быть известен на этапе компиляции или только во время выполнения.

```cpp
std::array<int, 3> a{1, 2, 3};
std::span s = a;

static_assert(s.extent == 3);
```

Для `std::vector` размер динамический.

```cpp
std::vector<int> v{1, 2, 3};
std::span s = v;

static_assert(decltype(s)::extent == std::dynamic_extent);
```

Динамический `span` хранит и указатель, и размер.

Статический `span` может хранить только указатель.

## std::mdspan

`std::mdspan` - невладеющий многомерный view на одномерную память.

```cpp
#include <mdspan>
#include <vector>

std::vector<int> data{1, 2, 3, 4, 5, 6};

std::mdspan matrix(data.data(), 2, 3);
```

Теперь `data` можно читать как матрицу `2 x 3`.

```cpp
for (std::size_t i = 0; i < matrix.extent(0); ++i) {
    for (std::size_t j = 0; j < matrix.extent(1); ++j) {
        matrix[i, j] *= 10;
    }
}
```

`extent(0)` - размер первого измерения.

`extent(1)` - размер второго измерения.

## Зачем нужен mdspan

Вектор векторов хранит строки матрицы в разных областях памяти.

```cpp
std::vector<std::vector<int>> matrix;
```

Это может хуже использовать кеш процессора.

А `std::mdspan` позволяет хранить данные одним плоским вектором и работать с ним как с матрицей.

```cpp
std::vector<int> data(rows * cols);
std::mdspan view(data.data(), rows, cols);
```

Типичный пример - матрица смежности графа.

## mdspan и extents

Размерности `mdspan` описываются отдельным типом `std::extents`.

Можно смешивать compile-time и runtime размеры.

```cpp
using Extents = std::extents<std::size_t, std::dynamic_extent, 4>;

std::vector<int> data(3 * 4);
std::mdspan<int, Extents> view(data.data(), 3);
```

Здесь число колонок `4` известно на этапе компиляции, а число строк `3` передается во время выполнения.

## Подводные камни

## 1. Висячий view

```cpp
std::span<int> bad() {
    std::vector<int> values{1, 2, 3};
    return values; // span на уничтоженный vector
}
```

Это относится и к `string_view`, и к `span`, и к `mdspan`.

## 2. Реаллокация ломает span

```cpp
std::vector<int> values{1, 2, 3};
std::span<int> view = values;

values.resize(1000);

// view может стать невалидным
```

Если буфер переехал, старый `span` указывает в старую память.

## 3. span требует непрерывную память

```cpp
std::list<int> values{1, 2, 3};

// std::span<int> view = values; // ошибка
```

`std::list` не подходит.

## 4. string_view не обязан быть null-terminated

```cpp
std::string_view text{"abc\0def", 7};
```

Нельзя бездумно передавать `text.data()` в C API, ожидающий `'\0'`.

## 5. mdspan тоже не владеет памятью

```cpp
std::vector<int> data(9);
std::mdspan matrix(data.data(), 3, 3);
```

`data` должен жить дольше, чем `matrix`.

## Саммари

- `std::string_view`, `std::span` и `std::mdspan` не владеют данными.
- Их удобно передавать по значению.
- `std::string_view` хранит указатель и размер строки.
- `std::string_view` не обязан заканчиваться `'\0'`.
- `std::span` хранит указатель и размер массива.
- `std::span` может менять исходные элементы, если это `span<T>`, а не `span<const T>`.
- `std::span` не страдает от pointer decay.
- У `std::span` есть `first`, `last`, `subspan`.
- `std::span` поддерживает статический и динамический extent.
- `std::mdspan` представляет одномерную память как многомерный массив.
- Размерности `mdspan` задаются через `std::extents`.
- Главный риск всех view - время жизни исходных данных и реаллокации.
