# 8. Готовые состояния функции

## Суть

Здесь под состоянием функции понимаем объект, который можно вызвать как функцию, но у него есть свои данные.

В C++ это обычно:

- функтор;
- лямбда с захватом;
- `std::function`.

Это важно для `ScopeGuard`: он хранит действие, которое надо выполнить позже.

## Обычная функция без состояния

```cpp
#include <iostream>

void print() {
    std::cout << "hello\n";
}

int main() {
    print();
}
```

Функция не хранит данные между вызовами.

## Пример 1: функтор

```cpp
#include <iostream>

struct Counter {
    int value = 0;

    void operator()() {
        ++value;
        std::cout << value << '\n';
    }
};

int main() {
    Counter counter;

    counter();
    counter();
}
```

Вывод:

```text
1
2
```

Разбор:

```cpp
counter();
```

Вызов выглядит как функция.

Но `counter` - объект, и внутри него хранится `value`.

## Пример 2: лямбда с захватом

```cpp
#include <iostream>

int main() {
    int x = 10;

    auto print = [x] {
        std::cout << x << '\n';
    };

    print();
}
```

Вывод:

```text
10
```

Разбор:

```cpp
[x]
```

Лямбда захватила копию `x`.

Теперь у лямбды есть состояние.

## Пример 3: захват по ссылке

```cpp
#include <iostream>

int main() {
    int x = 10;

    auto print = [&x] {
        std::cout << x << '\n';
    };

    x = 20;

    print();
}
```

Вывод:

```text
20
```

Разбор:

```cpp
[&x]
```

Лямбда хранит ссылку на `x`, а не копию.

## Пример 4: mutable lambda

```cpp
#include <iostream>

int main() {
    int x = 10;

    auto inc = [x]() mutable {
        ++x;
        std::cout << x << '\n';
    };

    inc();
    inc();

    std::cout << x << '\n';
}
```

Вывод:

```text
11
12
10
```

Разбор:

`x` внутри лямбды - копия.

`mutable` разрешает менять эту копию.

Исходный `x` не меняется.

## Пример 5: std::function

```cpp
#include <functional>
#include <iostream>

int main() {
    int x = 42;

    std::function<void()> action = [x] {
        std::cout << x << '\n';
    };

    action();
}
```

Вывод:

```text
42
```

`std::function<void()>` хранит любой вызываемый объект с такой сигнатурой.

Здесь он хранит лямбду.

## Пример 6: std::function в ScopeGuard

```cpp
#include <functional>
#include <iostream>

class ScopeGuard {
public:
    explicit ScopeGuard(std::function<void()> action)
        : action_(std::move(action)) {
    }

    ~ScopeGuard() {
        action_();
    }

private:
    std::function<void()> action_;
};

int main() {
    int id = 7;

    ScopeGuard guard([id] {
        std::cout << "cleanup " << id << '\n';
    });
}
```

Вывод:

```text
cleanup 7
```

Разбор:

```cpp
std::function<void()> action_;
```

`ScopeGuard` хранит действие.

```cpp
[id] { ... }
```

Действие хранит свое состояние: копию `id`.

## Опасность: ссылка живет меньше лямбды

```cpp
#include <functional>

std::function<void()> make_action() {
    int x = 42;

    return [&x] {
        // x уже уничтожен после выхода из make_action
    };
}
```

Проблема: лямбда хранит ссылку на локальную переменную.

После выхода из функции ссылка становится висячей.

Правильнее:

```cpp
return [x] {
    // захватили копию
};
```

## Что будет выведено

```cpp
#include <iostream>

int main() {
    int x = 1;

    auto f = [x]() mutable {
        ++x;
        std::cout << x << '\n';
    };

    x = 10;

    f();
    f();
    std::cout << x << '\n';
}
```

Вывод:

```text
2
3
10
```

## Саммари

- Функция сама по себе обычно не хранит состояние.
- Функтор - объект с `operator()`.
- Функтор может хранить состояние в полях.
- Лямбда с захватом тоже хранит состояние.
- Захват `[x]` хранит копию.
- Захват `[&x]` хранит ссылку.
- `mutable` разрешает менять копии внутри лямбды.
- `std::function` хранит любой вызываемый объект с подходящей сигнатурой.
- Нельзя возвращать лямбду со ссылкой на локальную переменную.
