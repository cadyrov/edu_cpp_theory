# 7. RAII и ScopeGuard: ресурс как объект

## Суть

RAII = Resource Acquisition Is Initialization.

Идея: ресурс захватывается в конструкторе, освобождается в деструкторе.

```cpp
class Resource {
public:
    Resource() {
        // захват ресурса
    }

    ~Resource() {
        // освобождение ресурса
    }
};
```

Когда объект выходит из области видимости, деструктор вызывается автоматически.

## Зачем нужен RAII

RAII защищает от:

- раннего `return`;
- исключений;
- забытых освобождений;
- сложных ветвлений.

Главная идея: не помнить про освобождение вручную.

## Пример 1: память как ресурс

```cpp
#include <memory>

void may_throw();

void foo() {
    auto p = std::make_unique<int>(42);

    may_throw();
}
```

Если `may_throw()` бросит исключение, `unique_ptr` все равно освободит память.

Разбор:

```cpp
auto p = std::make_unique<int>(42);
```

`p` владеет памятью.

```cpp
}
```

При выходе из функции вызывается деструктор `p`.

## Пример 2: свой RAII-класс

```cpp
#include <iostream>

class File {
public:
    File() {
        std::cout << "open\n";
    }

    ~File() {
        std::cout << "close\n";
    }
};

int main() {
    File file;
}
```

Вывод:

```text
open
close
```

Разбор:

```cpp
File file;
```

Конструктор захватывает ресурс.

```cpp
}
```

Деструктор освобождает ресурс.

## Пример 3: ранний return

```cpp
#include <iostream>

class Guard {
public:
    ~Guard() {
        std::cout << "cleanup\n";
    }
};

void foo(bool error) {
    Guard guard;

    if (error) {
        return;
    }
}
```

Если `error == true`, все равно будет:

```text
cleanup
```

## Пример 4: исключение

```cpp
#include <iostream>
#include <stdexcept>

class Guard {
public:
    ~Guard() {
        std::cout << "cleanup\n";
    }
};

void foo() {
    Guard guard;

    throw std::runtime_error("error");
}
```

При раскрутке стека деструктор `guard` будет вызван.

## RAII в стандартной библиотеке

Примеры RAII-типов:

- `std::unique_ptr`;
- `std::vector`;
- `std::string`;
- `std::fstream`;
- `std::lock_guard`;
- `std::jthread`.

## ScopeGuard

ScopeGuard - объект, который выполняет действие при выходе из области видимости.

Это обобщение RAII: ресурсом может быть не только память, но и любое действие очистки.

## Пример 5: простой ScopeGuard

```cpp
#include <functional>
#include <iostream>

class ScopeGuard {
public:
    explicit ScopeGuard(std::function<void()> action)
        : action_(std::move(action)) {
    }

    ~ScopeGuard() {
        if (active_) {
            action_();
        }
    }

    void dismiss() {
        active_ = false;
    }

private:
    std::function<void()> action_;
    bool active_ = true;
};

int main() {
    ScopeGuard guard([] {
        std::cout << "cleanup\n";
    });
}
```

Вывод:

```text
cleanup
```

## Пример 6: отмена ScopeGuard

```cpp
#include <functional>
#include <iostream>

class ScopeGuard {
public:
    explicit ScopeGuard(std::function<void()> action)
        : action_(std::move(action)) {
    }

    ~ScopeGuard() {
        if (active_) {
            action_();
        }
    }

    void dismiss() {
        active_ = false;
    }

private:
    std::function<void()> action_;
    bool active_ = true;
};

int main() {
    ScopeGuard guard([] {
        std::cout << "rollback\n";
    });

    guard.dismiss();
}
```

Вывода не будет.

Разбор:

```cpp
guard.dismiss();
```

Отключили действие на выходе из scope.

## Пример 7: rollback

```cpp
#include <functional>
#include <iostream>

class ScopeGuard {
public:
    explicit ScopeGuard(std::function<void()> action)
        : action_(std::move(action)) {
    }

    ~ScopeGuard() {
        if (active_) {
            action_();
        }
    }

    void dismiss() {
        active_ = false;
    }

private:
    std::function<void()> action_;
    bool active_ = true;
};

void save() {
    ScopeGuard rollback([] {
        std::cout << "rollback\n";
    });

    std::cout << "save\n";

    rollback.dismiss();
}
```

Вывод:

```text
save
```

Если `dismiss()` не вызвать, при выходе будет `rollback`.

## Boost.Scope

В реальном коде ScopeGuard часто не пишут вручную, а берут готовый.

В Boost для этого есть `boost::scope::scope_exit`.

```cpp
#include <boost/scope/scope_exit.hpp>
#include <iostream>

void foo() {
    boost::scope::scope_exit cleanup([] {
        std::cout << "cleanup\n";
    });

    std::cout << "body\n";
}
```

Вывод:

```text
body
cleanup
```

`scope_exit` выполняет переданное действие при выходе из области видимости.

Это работает при:

- обычном выходе;
- раннем `return`;
- исключении.

### Что позволяет Boost.Scope

`Boost.Scope` позволяет не писать свой ScopeGuard для типовых случаев.

Основные готовые варианты:

- `boost::scope::scope_exit` - выполнить действие при любом выходе из scope;
- `boost::scope::scope_fail` - выполнить действие только при выходе из-за исключения;
- `boost::scope::scope_success` - выполнить действие только при успешном выходе;
- `boost::scope::unique_resource` - хранить ресурс и функцию освобождения вместе.

Пример rollback только при ошибке:

```cpp
#include <boost/scope/scope_fail.hpp>
#include <iostream>
#include <stdexcept>

void save() {
    boost::scope::scope_fail rollback([] {
        std::cout << "rollback\n";
    });

    std::cout << "save\n";

    throw std::runtime_error("error");
}
```

Если функция выйдет через исключение, будет выполнен `rollback`.

## Важное правило

Деструктор не должен бросать исключения.

Плохо:

```cpp
~Guard() {
    throw;
}
```

Деструктор часто вызывается во время обработки другого исключения.

Если деструктор тоже бросит исключение, программа может завершиться через `std::terminate`.

## Что будет выведено

```cpp
#include <iostream>

class A {
public:
    A() {
        std::cout << "A\n";
    }

    ~A() {
        std::cout << "~A\n";
    }
};

int main() {
    A a;
    std::cout << "body\n";
}
```

Вывод:

```text
A
body
~A
```

## Саммари

- RAII связывает ресурс с временем жизни объекта.
- Конструктор захватывает ресурс.
- Деструктор освобождает ресурс.
- RAII работает при обычном выходе, раннем `return` и исключениях.
- `std::unique_ptr` - пример RAII для памяти.
- `std::lock_guard` - пример RAII для mutex.
- ScopeGuard выполняет произвольное действие при выходе из scope.
- ScopeGuard можно отключить через `dismiss`.
- `boost::scope::scope_exit` - готовый ScopeGuard из Boost.
- `boost::scope::scope_fail` и `boost::scope::scope_success` разделяют выход по ошибке и успешный выход.
- Деструкторы не должны бросать исключения.
