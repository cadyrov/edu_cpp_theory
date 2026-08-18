# 10. CRTP и cтатический полиморфизм

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

## Саммари

- CRTP передает тип наследника в базовый шаблон.
- Это статический полиморфизм без `virtual`.
- Вызовы могут инлайниться и не требуют vtable.
- CRTP полезен для общих операторов и интерфейсных примесей.
- Закрытый конструктор и `friend Derived` защищают от передачи неправильного типа наследника.
- Он не подходит для обычного хранения разных типов через общий базовый указатель.
