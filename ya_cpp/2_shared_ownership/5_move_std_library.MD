# 5. Семантика перемещения в стандартной библиотеке: указатели и контейнеры

## Суть

`std::move` не перемещает объект сам по себе.

Он разрешает использовать объект как источник для перемещения.

После перемещения стандартный объект остается валидным.

Но его значение обычно не нужно предполагать.

```cpp
#include <utility>

std::move(x);
```

Правило: moved-from объект можно уничтожить или присвоить ему новое значение.

## Пример 1: unique_ptr после move

```cpp
#include <iostream>
#include <memory>
#include <utility>

int main() {
    auto p1 = std::make_unique<int>(42);
    auto p2 = std::move(p1);

    std::cout << *p2 << '\n';
    std::cout << (p1 == nullptr) << '\n';
}
```

Вывод:

```text
42
1
```

`unique_ptr` передал владение.

После move `p1` стал пустым.

## Пример 2: shared_ptr после move

```cpp
#include <iostream>
#include <memory>
#include <utility>

int main() {
    auto p1 = std::make_shared<int>(42);
    auto p2 = std::move(p1);

    std::cout << *p2 << '\n';
    std::cout << (p1 == nullptr) << '\n';
}
```

Вывод:

```text
42
1
```

Перемещение `shared_ptr` передает сам объект-владелец.

Счетчик владельцев не увеличивается.

## Пример 3: vector после move

```cpp
#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = std::move(a);

    std::cout << b.size() << '\n';
    std::cout << a.size() << '\n';
}
```

Обычно вывод будет:

```text
3
0
```

Но полагаться на точное содержимое `a` после move не нужно.

`a` валиден, но его состояние не важно.

## Пример 4: map после move

```cpp
#include <iostream>
#include <map>
#include <string>
#include <utility>

int main() {
    std::map<std::string, int> source = {
        {"one", 1},
        {"two", 2}
    };

    std::map<std::string, int> target = std::move(source);

    std::cout << target["one"] << '\n';
}
```

Вывод:

```text
1
```

Данные перешли в `target`.

`source` можно уничтожить или заполнить заново.

## Пример 5: list после move

```cpp
#include <iostream>
#include <list>
#include <utility>

int main() {
    std::list<int> a = {1, 2, 3};
    std::list<int> b = std::move(a);

    std::cout << b.front() << '\n';
}
```

Вывод:

```text
1
```

У `list` перемещение обычно дешево: переносится владение узлами списка.

## Пример 6: array после move

```cpp
#include <array>
#include <iostream>
#include <string>
#include <utility>

int main() {
    std::array<std::string, 2> a = {"hello", "world"};
    std::array<std::string, 2> b = std::move(a);

    std::cout << b[0] << '\n';
    std::cout << b[1] << '\n';
}
```

Вывод:

```text
hello
world
```

`std::array` хранит элементы внутри себя.

При move перемещается каждый элемент.

У `array` нет отдельного динамического буфера, который можно просто передать.

## Подводные камни

### std::move не очищает объект

```cpp
std::vector<int> a = {1, 2, 3};
std::move(a);
```

Эта строка сама по себе ничего полезного не делает.

Нужен получатель:

```cpp
auto b = std::move(a);
```

### Не используйте moved-from объект как обычный

Плохо:

```cpp
auto b = std::move(a);
std::cout << a[0] << '\n';
```

После move не стоит читать старое содержимое контейнера.

Лучше присвоить новое значение:

```cpp
a = {10, 20, 30};
```

### const мешает перемещению

```cpp
const std::vector<int> a = {1, 2, 3};
auto b = std::move(a);
```

`std::move(a)` даст `const` rvalue.

Часто это приведет к копированию, а не к перемещению.

### move не всегда дешевый

`vector`, `map`, `list`, `string` обычно перемещаются дешево.

`std::array` перемещает элементы по одному.

Если элементы дорогие для перемещения, `array` тоже будет дорогим.

## Что будет выведено

```cpp
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

int main() {
    auto p1 = std::make_unique<int>(7);
    auto p2 = std::move(p1);

    std::vector<int> a = {1, 2};
    auto b = std::move(a);

    std::cout << *p2 << '\n';
    std::cout << (p1 == nullptr) << '\n';
    std::cout << b.size() << '\n';
}
```

Вывод:

```text
7
1
2
```

## Саммари

- `std::move` разрешает перемещение, но сам ничего не переносит.
- После move объект остается валидным.
- Moved-from объект можно уничтожить или присвоить ему новое значение.
- `unique_ptr` после move обычно `nullptr`.
- `shared_ptr` после move обычно `nullptr`.
- У контейнеров после move не стоит читать старое содержимое.
- `vector`, `map`, `list` обычно перемещаются дешево.
- `std::array` перемещает элементы по одному.
- `const` объект обычно нельзя нормально переместить.
