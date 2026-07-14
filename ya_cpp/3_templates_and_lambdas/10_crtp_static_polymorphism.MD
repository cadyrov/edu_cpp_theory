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
- Он не подходит для обычного хранения разных типов через общий базовый указатель.
