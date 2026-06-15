# 2. Опасности и ограничения использования std::shared_ptr

## Суть

`std::shared_ptr` решает проблему времени жизни объекта, но не должен быть указателем по умолчанию.

Он нужен только там, где владение действительно совместное.

Главные проблемы:

- циклы владения;
- лишнее продление жизни объекта;
- неочевидные копии;
- неправильное создание из сырого указателя.

## Пример 1: shared_ptr там, где нужен unique_ptr

```cpp
#include <memory>

struct Config {
    int value = 42;
};

int main() {
    auto config = std::make_shared<Config>();
}
```

Код работает.

Но если у объекта один владелец, лучше так:

```cpp
#include <memory>

struct Config {
    int value = 42;
};

int main() {
    auto config = std::make_unique<Config>();
}
```

`unique_ptr` точнее выражает смысл: владелец один.

## Пример 2: лишнее владение в функции

```cpp
#include <iostream>
#include <memory>

void print(std::shared_ptr<int> p) {
    std::cout << *p << '\n';
}

int main() {
    auto value = std::make_shared<int>(42);

    print(value);
}
```

Функция `print` получает копию `shared_ptr`.

На время вызова она становится владельцем.

Если функция только читает значение, владение ей не нужно:

```cpp
void print(const int& value) {
    std::cout << value << '\n';
}
```

Вызов:

```cpp
print(*value);
```

## Пример 3: цикл владения

```cpp
#include <iostream>
#include <memory>

struct Node {
    std::shared_ptr<Node> next;

    ~Node() {
        std::cout << "destroy\n";
    }
};

int main() {
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();

    a->next = b;
    b->next = a;
}
```

Вывод:

```text
```

Ничего не будет выведено.

`a` владеет `b`, а `b` владеет `a`.

Счетчики не становятся нулевыми, поэтому объекты не уничтожаются.

## Пример 4: разрыв цикла через weak_ptr

```cpp
#include <iostream>
#include <memory>

struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;

    ~Node() {
        std::cout << "destroy\n";
    }
};

int main() {
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();

    a->next = b;
    b->prev = a;
}
```

Вывод:

```text
destroy
destroy
```

`next` владеет следующим узлом.

`prev` только смотрит назад и не продлевает жизнь объекта.

## Пример 5: use_count для логики

```cpp
#include <iostream>
#include <memory>

void update(std::shared_ptr<int> p) {
    if (p.use_count() == 1) {
        *p = 100;
    }
}

int main() {
    auto value = std::make_shared<int>(42);

    update(value);

    std::cout << *value << '\n';
}
```

Вывод:

```text
42
```

Разбор:

```cpp
void update(std::shared_ptr<int> p)
```

При вызове создается копия `shared_ptr`.

Внутри функции счетчик уже не `1`.

`use_count()` легко дает не то, что ожидается.

## Пример 6: два shared_ptr из одного сырого указателя

```cpp
#include <memory>

int main() {
    int* raw = new int(42);

    std::shared_ptr<int> p1(raw);
    std::shared_ptr<int> p2(raw);
}
```

Так делать нельзя.

`p1` и `p2` создали два разных блока управления для одного объекта.

Оба попробуют удалить один и тот же `int`.

Правильно:

```cpp
auto p1 = std::make_shared<int>(42);
auto p2 = p1;
```

## Пример 7: shared_ptr на this

```cpp
#include <memory>

struct Item {
    std::shared_ptr<Item> get_ptr() {
        return std::shared_ptr<Item>(this);
    }
};
```

Так делать нельзя.

Создается новый `shared_ptr`, который не знает о существующих владельцах.

Для такого случая нужен `std::enable_shared_from_this`.

```cpp
#include <memory>

struct Item : std::enable_shared_from_this<Item> {
    std::shared_ptr<Item> get_ptr() {
        return shared_from_this();
    }
};

int main() {
    auto item = std::make_shared<Item>();
    auto same = item->get_ptr();
}
```

`shared_from_this()` возвращает `shared_ptr` из уже существующего блока управления.

## Подводные камни

### shared_ptr скрывает владельцев

Когда `shared_ptr` передается по коду слишком широко, становится сложно понять, кто реально отвечает за жизнь объекта.

Если владение не нужно, лучше использовать:

- `T&`;
- `const T&`;
- `T*`;
- `std::weak_ptr<T>`.

### Циклы не удаляются автоматически

`shared_ptr` считает владельцев.

Он не понимает, что группа объектов владеет только сама собой.

Для обратных ссылок обычно нужен `weak_ptr`.

### make_shared обычно лучше new

Плохо:

```cpp
std::shared_ptr<int> p(new int(42));
```

Лучше:

```cpp
auto p = std::make_shared<int>(42);
```

Так короче и безопаснее.

### shared_ptr не делает объект потокобезопасным

Счетчик владельцев защищен.

Сам объект внутри `shared_ptr` нужно защищать отдельно.

## Что будет выведено

```cpp
#include <iostream>
#include <memory>

struct A {
    std::shared_ptr<A> other;

    ~A() {
        std::cout << "~A\n";
    }
};

int main() {
    auto x = std::make_shared<A>();
    auto y = std::make_shared<A>();

    x->other = y;
    y->other = x;

    std::cout << x.use_count() << '\n';
    std::cout << y.use_count() << '\n';
}
```

Вывод:

```text
2
2
```

`~A` не будет выведен.

Объекты держат друг друга через `shared_ptr`.

## Саммари

- `shared_ptr` нужен только для реального совместного владения.
- Если владелец один, лучше `unique_ptr`.
- Если функция только читает объект, лучше ссылка.
- Копирование `shared_ptr` меняет счетчик владельцев.
- Циклы из `shared_ptr` приводят к утечкам.
- Для обратных ссылок обычно нужен `weak_ptr`.
- Не создавайте несколько `shared_ptr` из одного сырого указателя.
- Не создавайте `shared_ptr<T>(this)`.
- `use_count()` не стоит использовать для бизнес-логики.
- `shared_ptr` управляет временем жизни, но не синхронизацией данных.
