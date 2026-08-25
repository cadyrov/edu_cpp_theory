# 1. std::shared_ptr и std::weak_ptr: совместное владение ресурсом

## Суть

`std::shared_ptr` - умный указатель для совместного владения объектом.

Совместное владение означает: у объекта может быть несколько владельцев.

Объект уничтожается, когда исчезает последний `shared_ptr`.

```cpp
#include <memory>

int main() {
    auto p = std::make_shared<int>(42);
}
```

`delete` писать не нужно.

## Зачем нужен

`shared_ptr` нужен, когда объект действительно должен жить, пока им пользуются несколько частей программы.

Например, один объект хранится в кэше и одновременно используется в нескольких местах.

```cpp
#include <memory>
#include <string>

struct User {
    std::string name;
};

int main() {
    auto user = std::make_shared<User>();
}
```

## Пример 1: базовое владение

```cpp
#include <iostream>
#include <memory>

int main() {
    auto p = std::make_shared<int>(42);

    std::cout << *p << '\n';
}
```

Вывод:

```text
42
```

Разбор:

```cpp
auto p = std::make_shared<int>(42);
```

Создали `int` в динамической памяти.

Владельцем стал `p`.

В конце `main` последний владелец исчезает, и объект удаляется.

## Пример 2: копирование добавляет владельца

```cpp
#include <iostream>
#include <memory>

int main() {
    auto p1 = std::make_shared<int>(42);
    auto p2 = p1;

    std::cout << *p1 << '\n';
    std::cout << *p2 << '\n';
    std::cout << p1.use_count() << '\n';
}
```

Вывод:

```text
42
42
2
```

Разбор:

```cpp
auto p2 = p1;
```

`p1` и `p2` теперь владеют одним объектом.

Счетчик владельцев стал равен `2`.

## Пример 3: объект живет до последнего владельца

```cpp
#include <iostream>
#include <memory>

struct Item {
    ~Item() {
        std::cout << "destroy\n";
    }
};

int main() {
    auto p1 = std::make_shared<Item>();

    {
        auto p2 = p1;
    }

    std::cout << "still alive\n";
}
```

Вывод:

```text
still alive
destroy
```

Разбор:

`p2` исчез раньше, но `p1` еще владеет объектом.

Объект уничтожается только в конце `main`.

## Пример 4: weak_ptr не владеет объектом

```cpp
#include <iostream>
#include <memory>

int main() {
    auto p = std::make_shared<int>(42);
    std::weak_ptr<int> w = p;

    std::cout << p.use_count() << '\n';
}
```

Вывод:

```text
1
```

`weak_ptr` смотрит на объект, но не увеличивает счетчик владельцев.

Он не продлевает жизнь объекта.

## Пример 5: lock

```cpp
#include <iostream>
#include <memory>

int main() {
    std::weak_ptr<int> w;

    {
        auto p = std::make_shared<int>(42);
        w = p;

        if (auto locked = w.lock()) {
            std::cout << *locked << '\n';
        }
    }

    if (auto locked = w.lock()) {
        std::cout << *locked << '\n';
    } else {
        std::cout << "expired\n";
    }
}
```

Вывод:

```text
42
expired
```

Разбор:

```cpp
auto locked = w.lock()
```

`lock()` пытается получить `shared_ptr`.

Если объект еще жив, вернется непустой `shared_ptr`.

Если объект уже уничтожен, вернется пустой `shared_ptr`.

## Пример 6: передача в функцию

```cpp
#include <iostream>
#include <memory>

void print(std::shared_ptr<int> p) {
    std::cout << *p << '\n';
}

int main() {
    auto p = std::make_shared<int>(42);

    print(p);
}
```

Функция получает свою копию `shared_ptr`.

На время вызова она тоже становится владельцем объекта.

Если владение не нужно, лучше передать ссылку:

```cpp
void print(const int& value) {
    std::cout << value << '\n';
}
```

## Подводные камни

### shared_ptr не должен быть указателем по умолчанию

Если у объекта один владелец, нужен `std::unique_ptr`.

Если функция только читает объект, часто достаточно ссылки или сырого указателя без владения.

### Нельзя создавать два shared_ptr из одного сырого указателя

Плохо:

```cpp
int* raw = new int(42);

std::shared_ptr<int> p1(raw);
std::shared_ptr<int> p2(raw);
```

`p1` и `p2` думают, что каждый владеет объектом отдельно.

В итоге оба попытаются вызвать `delete`.

Правильно:

```cpp
auto p1 = std::make_shared<int>(42);
auto p2 = p1;
```

### weak_ptr нужно проверять через lock

Плохо думать, что объект точно жив:

```cpp
std::weak_ptr<int> w;

auto p = w.lock();
std::cout << *p << '\n'; // p может быть пустым
```

Правильно:

```cpp
if (auto p = w.lock()) {
    std::cout << *p << '\n';
}
```

### use_count не должен управлять логикой

`use_count()` полезен для учебных примеров и отладки.

В реальном коде логика вида "если владельцев ровно один" часто ломкая.

## Что будет выведено

```cpp
#include <iostream>
#include <memory>

int main() {
    auto p1 = std::make_shared<int>(10);
    std::weak_ptr<int> w = p1;

    {
        auto p2 = p1;
        std::cout << p1.use_count() << '\n';
    }

    std::cout << p1.use_count() << '\n';

    p1.reset();

    if (w.expired()) {
        std::cout << "expired\n";
    }
}
```

Вывод:

```text
2
1
expired
```

## Саммари

- `std::shared_ptr` выражает совместное владение.
- Объект уничтожается, когда исчезает последний владелец.
- Копирование `shared_ptr` увеличивает счетчик владельцев.
- `std::make_shared` обычно лучше прямого `new`.
- `std::weak_ptr` не владеет объектом.
- `weak_ptr` не продлевает жизнь объекта.
- Чтобы получить объект из `weak_ptr`, нужен `lock()`.
- Результат `lock()` нужно проверять.
- `use_count()` не стоит использовать как основу логики.
