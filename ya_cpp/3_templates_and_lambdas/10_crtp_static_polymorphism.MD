# 10. CRTP, миксины и явный параметр this

## Суть

CRTP - идиома, где базовый шаблонный класс принимает наследника как параметр.

```cpp
template <typename Derived>
struct Base {
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};
```

Это дает полиморфизм без `virtual`.

Миксин — класс, который через наследование добавляет другому классу готовое
поведение. Такие миксины часто реализуют с помощью CRTP.

В C++23 появился явный параметр `this`: он позволяет записать объект метода как
обычный параметр.

## Примеры

### Пример 1: базовый CRTP

```cpp
#include <iostream>

template <typename Derived>
struct Drawable {
    void draw() {
        static_cast<Derived*>(this)->draw_impl();
    }
};

struct Circle : Drawable<Circle> {
    void draw_impl() {
        std::cout << "circle\n";
    }
};

int main() {
    Circle c;
    c.draw();
}
```

### Пример 2: общий оператор

```cpp
template <typename Derived>
struct Equality {
    friend bool operator!=(const Derived& a, const Derived& b) {
        return !(a == b);
    }
};

struct User : Equality<User> {
    int id;

    friend bool operator==(const User& a, const User& b) {
        return a.id == b.id;
    }
};
```

### Пример 3: статический интерфейс

```cpp
template <typename T>
void render(Drawable<T>& object) {
    object.draw();
}
```

Вызов решается на этапе компиляции.

### Пример 4: копирование конкретного типа

CRTP-база может вернуть объект именно того типа, который от неё наследуется.

```cpp
template <typename Derived>
struct Cloneable {
    Derived clone() const {
        return static_cast<const Derived&>(*this);
    }
};

struct Document : Cloneable<Document> {
    int id;
};
```

### Пример 5: миксин

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

### Пример 6: несколько миксинов

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

### Пример 7: явный параметр this

```cpp
struct Counter {
    int value = 0;

    void inc(this Counter& self) {
        ++self.value;
    }
};
```

`self` — явный объект, на котором вызван метод. Для такой записи нужен C++23.

## Подводные камни

Нужно передавать правильный тип наследника.

```cpp
struct Bad : Drawable<Circle> {}; // ошибка дизайна
```

Компилятор сам по себе не запрещает такую ошибку. Базовый класс можно защитить:
сделать его конструктор закрытым и открыть к нему доступ только типу `Derived`.

```cpp
template <typename Derived>
class SafeBase {
private:
    SafeBase() = default;
    friend Derived;

public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

struct Good : SafeBase<Good> {
    void implementation() {}
};

struct Other {};
struct Bad : SafeBase<Other> {}; // ошибка: конструктор SafeBase закрыт
```

`Good` имеет доступ к конструктору `SafeBase<Good>`, потому что объявлен другом.
У `Bad` такого доступа нет: другом `SafeBase<Other>` является только `Other`.

CRTP не заменяет обычный runtime-полиморфизм.

```cpp
std::vector<std::unique_ptr<Base>> objects;
```

Для такого хранения нужны виртуальные функции или другой механизм.

Ошибки CRTP часто длиннее обычных ошибок.

Если у наследника нет нужного метода, ошибка появится в шаблоне.

```cpp
struct Square : Drawable<Square> {};

Square s;
s.draw(); // нет draw_impl
```

То же ограничение есть у миксинов: наследник должен реализовать ожидаемые
методы. Большое количество миксинов также может усложнить класс и привести к
конфликтам имён.

```cpp
struct X : A<X>, B<X>, C<X>, D<X> {};
```

Явный параметр `this` не нужен для обычных методов. Вместо
`void inc(this Counter& self)` чаще достаточно написать обычный `void inc()`.
Он полезен, когда упрощает шаблонный код или перегрузки по категории значения.

## Саммари

- CRTP передает тип наследника в базовый шаблон.
- Это статический полиморфизм без `virtual`.
- Вызовы могут инлайниться и не требуют vtable.
- CRTP полезен для общих операторов и интерфейсных примесей.
- Миксин добавляет поведение через наследование и требует от наследника ожидаемый интерфейс.
- Явный `this` делает объект метода обычным параметром и требует C++23.
- Закрытый конструктор и `friend Derived` защищают от передачи неправильного типа наследника.
- Он не подходит для обычного хранения разных типов через общий базовый указатель.
