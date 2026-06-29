# 10. Миксины, явный параметр this

## Суть

Миксин - класс, который добавляет готовое поведение другому классу.

```cpp
template <typename Derived>
struct Printable {
    void print() const {
        static_cast<const Derived*>(this)->print_impl();
    }
};
```

В C++23 появился явный параметр `this`: можно явно указать объект, для которого вызван метод.

## Примеры

### Пример 1: миксин

```cpp
#include <iostream>

template <typename Derived>
struct Printable {
    void print() const {
        static_cast<const Derived*>(this)->print_impl();
    }
};

struct User : Printable<User> {
    int id;

    void print_impl() const {
        std::cout << id << '\n';
    }
};
```

### Пример 2: несколько миксинов

```cpp
template <typename Derived>
struct Resettable {
    void reset() {
        static_cast<Derived*>(this)->reset_impl();
    }
};

struct Widget : Printable<Widget>, Resettable<Widget> {
    void print_impl() const {}
    void reset_impl() {}
};
```

### Пример 3: явный this

```cpp
struct Counter {
    int value = 0;

    void inc(this Counter& self) {
        ++self.value;
    }
};
```

`self` - явный объект, на котором вызван метод.

## Подводные камни

Миксин требует соглашения: наследник должен реализовать нужные методы.

```cpp
struct Bad : Printable<Bad> {};

Bad b;
b.print(); // нет print_impl
```

Много миксинов могут сделать класс трудным для чтения.

```cpp
struct X : A<X>, B<X>, C<X>, D<X> {};
```

Явный параметр `this` требует C++23 и поддержки компилятора.

Он не нужен для обычных методов.

```cpp
void inc() {
    ++value;
}
```

Используй его там, где он реально упрощает шаблонный код или перегрузки по категории значения.

## Саммари

- Миксин добавляет поведение через наследование.
- Часто миксины пишут через CRTP.
- Наследник должен соблюдать ожидаемый интерфейс.
- Явный `this` делает объект метода обычным параметром.
- Явный `this` полезен в C++23, но не обязателен для простых методов.

