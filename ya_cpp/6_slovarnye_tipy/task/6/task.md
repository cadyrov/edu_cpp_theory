# Практика со `std::variant`

## Задание 1. Безопасная обёртка над `union`

Доработайте класс `Data`:

- добавьте в хранилище `Point2D`;
- создавайте классы через `std::construct_at`;
- реализуйте `Destroy()` с вызовами `std::destroy_at`;
- вызывайте `Destroy()` перед сменой типа и в деструкторе.

```cpp
#include <memory>

struct Point2D {
    int x;
    int y;
};

struct Point3D {
    int x;
    int y;
    int z;
};

class Data {
public:
    enum class Type { None, P2D, P3D, Int };

    Data() = default;
    ~Data() {
        // Ваш код здесь.
    }

    void SetPoint2D(const Point2D& point) {
        // Ваш код здесь.
    }

    void SetPoint3D(const Point3D& point) {
        // Ваш код здесь.
    }

    void SetInt(int value) {
        // Ваш код здесь.
    }

private:
    void Destroy() {
        // Ваш код здесь.
    }

    union Storage {
        Point2D point2d;
        Point3D point3d;
        int integer;

        Storage() {}
        ~Storage() {}
    } data_;

    Type type_ = Type::None;
};
```

`std::construct_at` требует C++20.

## Задание 2. Печать уникальных типов

Напишите функцию `Print`, принимающую `std::variant<std::string, double, int>`.

Выводите вместе со значением:

- `Получен std::string`;
- `Получен double`;
- `Получен int`.

```cpp
#include <string>
#include <variant>

using Value = std::variant<std::string, double, int>;

void Print(const Value& value) {
    // Ваш код здесь.
}
```

Используйте `std::holds_alternative` и `std::get`.

## Задание 3. Повторяющийся тип

Измените функцию `Print`, чтобы она принимала:

```cpp
using Value = std::variant<std::string, double, std::string>;
```

Для альтернатив `0` и `2` выводите `Получена строка {значение}`, для альтернативы `1` — `Получено число {значение}`.

## Подсказки

- При повторении типа `std::get<T>` и `holds_alternative<T>` использовать нельзя.
- Проверяйте `value.index()` и извлекайте значение через `std::get<I>`.
- Перед созданием нового нетривиального члена `union` уничтожьте активный объект.
