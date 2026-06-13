# 4. Современная реализация идиомы PImpl

## Суть

PImpl = Pointer to Implementation.

Идея: в заголовке оставить только публичный интерфейс, а детали реализации спрятать в `.cpp`.

```cpp
class Widget {
public:
    Widget();
    ~Widget();

    void draw();

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
```

Пользователь класса видит `Widget`, но не видит поля `Impl`.

## Зачем нужен PImpl

- скрыть детали реализации;
- уменьшить зависимости в заголовке;
- ускорить пересборку;
- сохранить стабильный публичный интерфейс;
- убрать приватные поля из `.h`.

## Пример

### widget.h

```cpp
#pragma once

#include <memory>

class Widget {
public:
    Widget();
    ~Widget();

    void draw();

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
```

### widget.cpp

```cpp
#include "widget.h"

#include <iostream>
#include <string>

struct Widget::Impl {
    std::string title = "main widget";

    void draw() {
        std::cout << title << '\n';
    }
};

Widget::Widget()
    : impl_(std::make_unique<Impl>()) {
}

Widget::~Widget() = default;

void Widget::draw() {
    impl_->draw();
}
```

### main.cpp

```cpp
#include "widget.h"

int main() {
    Widget widget;

    widget.draw();
}
```

Вывод:

```text
main widget
```

## Разбор

```cpp
struct Impl;
```

Это предварительное объявление вложенного типа.

В заголовке не нужно знать, какие поля есть у `Impl`.

```cpp
std::unique_ptr<Impl> impl_;
```

`Widget` единолично владеет реализацией.

```cpp
struct Widget::Impl {
    std::string title = "main widget";
};
```

Полное определение `Impl` находится в `.cpp`.

## Почему деструктор в .cpp

Так делать правильно:

```cpp
// widget.h
~Widget();
```

```cpp
// widget.cpp
Widget::~Widget() = default;
```

Причина: `std::unique_ptr<Impl>` должен удалить `Impl`.

Для удаления нужен полный тип `Impl`.

В `.h` тип `Impl` неполный:

```cpp
struct Impl;
```

В `.cpp` тип уже полный:

```cpp
struct Widget::Impl {
    std::string title;
};
```

Поэтому деструктор `Widget` определяют в `.cpp`.

## Копирование запрещено

По умолчанию `Widget` нельзя копировать, потому что внутри `std::unique_ptr`.

```cpp
Widget a;
Widget b = a; // ошибка компиляции
```

Это нормально, если объект должен иметь уникальную реализацию.

Можно явно запретить:

```cpp
class Widget {
public:
    Widget();
    ~Widget();

    Widget(const Widget&) = delete;
    Widget& operator=(const Widget&) = delete;

    void draw();

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
```

## Перемещение

Перемещение можно разрешить:

### widget.h

```cpp
class Widget {
public:
    Widget();
    ~Widget();

    Widget(const Widget&) = delete;
    Widget& operator=(const Widget&) = delete;

    Widget(Widget&&) noexcept;
    Widget& operator=(Widget&&) noexcept;

    void draw();

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
```

### widget.cpp

```cpp
Widget::Widget(Widget&&) noexcept = default;
Widget& Widget::operator=(Widget&&) noexcept = default;
```

## Что будет выведено

```cpp
Widget a;
Widget b = std::move(a);

b.draw();
```

Вывод:

```text
main widget
```

Разбор: владение `Impl` перешло из `a` в `b`.

После перемещения `a` находится в корректном, но пустом состоянии.

## Частая ошибка

```cpp
class Widget {
public:
    Widget() = default;
    ~Widget() = default; // плохо для PImpl в заголовке

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
```

Проблема: деструктор определен в месте, где `Impl` еще неполный.

Решение: объявить в `.h`, определить в `.cpp`.

## Саммари

- PImpl прячет реализацию класса в `.cpp`.
- В `.h` остается публичный интерфейс и `std::unique_ptr<Impl>`.
- `Impl` в `.h` объявлен предварительно.
- Полное определение `Impl` находится в `.cpp`.
- Деструктор класса с PImpl нужно определять в `.cpp`.
- Копирование обычно запрещают.
- Перемещение можно разрешить через move constructor и move assignment.
- PImpl уменьшает зависимости и пересборки.
