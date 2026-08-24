# 7. Паттерны с `std::variant`

## Суть

Ручная обработка `variant` через `holds_alternative` и `get` многословна и легко пропускает новый тип.

```cpp
if (std::holds_alternative<int>(value)) {
    Print(std::get<int>(value));
} else if (std::holds_alternative<double>(value)) {
    Print(std::get<double>(value));
}
```

`std::visit` сам вызывает обработчик с активным значением и проверяет на этапе компиляции, что посетитель применим ко всем альтернативам.

## Базовый `std::visit`

```cpp
std::variant<std::string, double, int> value = 42;

std::visit([](const auto& item) {
    std::cout << item;
}, value);
```

Обобщённая лямбда создаёт подходящий `operator()` для каждого возможного типа.

С C++26 для одного варианта доступен метод `variant::visit`:

```cpp
value.visit([](const auto& item) {
    std::cout << item;
});
```

Свободная функция `std::visit` остаётся нужна в том числе для посещения нескольких `variant` одновременно.

## Ссылки и перемещение

Тип аргумента посетителя зависит от категории переданного `variant`:

```cpp
std::visit([](auto& item) {}, value);             // T&
std::visit([](const auto& item) {}, std::as_const(value)); // const T&
std::visit([](auto&& item) {}, std::move(value)); // T&&
```

`auto&&` в обобщённой лямбде — forwarding reference: для lvalue-варианта он выводится как `T&`, для rvalue — как `T&&`.

Если содержимое нужно передать дальше без лишних копий:

```cpp
auto result = std::visit(
    [](auto&& item) {
        return JsonData{
            std::forward<decltype(item)>(item)
        };
    },
    std::move(rawData)
);
```

После такого вызова активный объект может остаться в перемещённом состоянии.

## Возвращаемое значение

`std::visit` может вернуть результат посетителя:

```cpp
using Input = std::variant<int, double, std::string>;

DisplayValue Convert(const Input& input) {
    return std::visit([](const auto& value) -> DisplayValue {
        return DisplayValue{value};
    }, input);
}
```

Все ветки обычного `std::visit` должны возвращать один и тот же тип и категорию значения. Если нужен явно заданный общий тип, используйте `std::visit<R>`.

## Класс-посетитель

Вместо лямбды можно создать переиспользуемый функтор с несколькими перегрузками:

```cpp
struct Printer {
    void operator()(int value) const {
        std::cout << "int: " << value;
    }

    void operator()(double value) const {
        std::cout << "double: " << value;
    }

    void operator()(const std::string& value) const {
        std::cout << "string: " << value;
    }
};

std::visit(Printer{}, value);
```

Класс удобен, если обработчик хранит состояние или используется в нескольких местах.

## Паттерн Overloaded

Overloaded объединяет несколько лямбд в один набор перегрузок `operator()`.

```cpp
template <class... Ts>
struct Overloaded : Ts... {
    using Ts::operator()...;
};

// Нужно для CTAD в C++17.
template <class... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;
```

Применение:

```cpp
std::visit(Overloaded{
    [](int value) {
        std::cout << "int: " << value;
    },
    [](double value) {
        std::cout << "double: " << value;
    },
    [](const std::string& value) {
        std::cout << "string: " << value;
    }
}, variant);
```

Если добавить альтернативу в `variant`, необработанный тип приведёт к ошибке компиляции. Это даёт проверку полноты обработчиков.

## Обобщённая ветка

Одинаковые типы можно обработать одной лямбдой с ограничением:

```cpp
std::visit(Overloaded{
    [](std::integral auto value) {
        HandleInteger(value);
    },
    [](const std::string& value) {
        HandleText(value);
    }
}, variant);
```

Catch-all ветка с `auto&&` может дать понятную ошибку, но она отменяет compile-time проверку полноты, если просто принимает любой тип.

Для зависимого `static_assert` до C++23 используйте:

```cpp
template <typename>
inline constexpr bool alwaysFalse = false;

[](auto&& value) {
    using T = std::remove_cvref_t<decltype(value)>;
    static_assert(alwaysFalse<T>, "Unsupported type");
}
```

## Value-based полиморфизм

Закрытый набор объектов можно хранить по значению без базового класса:

```cpp
struct Circle {
    double radius;
};

struct Square {
    double side;
};

using Shape = std::variant<Circle, Square>;
```

Операции описываются отдельно:

```cpp
double Area(const Shape& shape) {
    return std::visit(Overloaded{
        [](const Circle& circle) {
            return 3.14159 * circle.radius * circle.radius;
        },
        [](const Square& square) {
            return square.side * square.side;
        }
    }, shape);
}
```

## Сравнение видов полиморфизма

| Критерий | Виртуальные функции | `variant` + `visit` |
|---|---|---|
| Набор типов | Открытый | Закрытый |
| Добавить новый тип | Обычно легко | Нужно изменить `variant` и посетителей |
| Добавить новую операцию | Нужно менять интерфейс/классы | Новая функция-посетитель |
| Хранение | Часто указатели и динамическая память | Значения непосредственно в `variant` |
| Диспетчеризация | Через vtable | По индексу альтернативы |
| Размер элемента | Размер объекта конкретного типа | Размер крупнейшей альтернативы плюс служебные данные |
| Связь типов | Общий базовый интерфейс | Типы могут быть независимыми |

`variant` не гарантированно быстрее виртуального вызова: результат зависит от числа альтернатив, реализации, расположения данных и оптимизаций. Выбирайте прежде всего по модели расширения.

## Подводные камни

### 1. Посетитель должен поддерживать все альтернативы

Ошибка `invoke_result` или подстановки шаблона часто означает, что хотя бы для одного типа нет допустимого вызова.

### 2. Конкретная `T&&` не принимает значение из lvalue-варианта

Если в `std::visit(visitor, variant)` передан lvalue, обработчик получает `T&`. Используйте `T&`, `const T&`, обобщённую `auto&&` или передайте `std::move(variant)`.

### 3. Все ветки должны согласовать результат

Возврат `int` из одной лямбды и `double` из другой обычно не выводит общий тип автоматически. Задайте единый возвращаемый тип.

### 4. Catch-all может скрыть забытый вариант

Лямбда `[](auto&&) { ... }` делает посетителя формально полным, поэтому новый тип больше не вызывает ошибку компиляции.

### 5. `std::move(variant)` не меняет активный индекс

Он разрешает переместить активное значение, но сам `variant` остаётся объектом с тем же вариантом и допустимым, хотя перемещённым содержимым.

### 6. `visit` бросает для `valueless_by_exception`

Если вариант не содержит значения из-за исключения при смене альтернативы, посещение приводит к `std::bad_variant_access`.

### 7. `variant::visit` требует C++26

Для C++17–23 используйте свободную функцию `std::visit`.

## Саммари

- `std::visit` выполняет типобезопасную диспетчеризацию по активной альтернативе.
- Посетитель обязан поддерживать каждый возможный тип.
- Overloaded объединяет несколько лямбд в один набор перегрузок.
- Категория аргумента зависит от категории переданного `variant`.
- `visit` может возвращать значение, но результаты всех веток должны совпадать.
- `variant` подходит для value-based полиморфизма с закрытым набором типов.
- В C++26 для одного варианта доступен метод `variant::visit`.
