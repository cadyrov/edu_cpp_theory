# 7. `view_interface` и пользовательские отображения

## Суть

Собственное отображение нужно, когда готовых `std::views` недостаточно. Оно должно:

- удовлетворять `std::ranges::range`;
- быть перемещаемым;
- распознаваться как `view`;
- предоставлять `begin()`, `end()` и подходящий итератор.

Удобнее наследоваться от `std::ranges::view_interface`.

```cpp
template <class V>
class cycle_view
    : public std::ranges::view_interface<cycle_view<V>> {
    // ...
};
```

## Зачем нужен `view_interface`

Базовый класс добавляет доступные для конкретного диапазона методы, например:

- `empty()`;
- `front()`;
- `back()`;
- `data()`;
- `size()`;
- преобразование в `bool`.

Набор методов зависит от возможностей итератора и ограничителя. Само отображение всё равно обязано реализовать границы и логику итерации.

## CRTP

`view_interface` использует CRTP — базовый класс получает тип наследника как шаблонный параметр:

```cpp
template <class Derived>
class Base {
public:
    void interface() {
        static_cast<Derived&>(*this).implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() {}
};
```

Так базовый класс вызывает методы наследника без виртуальных функций и расходов динамического полиморфизма.

## Состав пользовательского view

Минимальный каркас:

```cpp
template <std::ranges::view V>
class cycle_view
    : public std::ranges::view_interface<cycle_view<V>> {
public:
    cycle_view() = default;

    explicit cycle_view(V base)
        : base_(std::move(base)) {}

    class iterator {
        // состояние и операции итератора
    };

    auto begin() {
        return iterator{
            std::ranges::begin(base_),
            std::ranges::begin(base_),
            std::ranges::end(base_)
        };
    }

    auto end() const {
        return std::unreachable_sentinel;
    }

private:
    V base_;
};
```

`std::unreachable_sentinel` обозначает бесконечный диапазон.

## Итератор циклического view

Итератор хранит текущую позицию и границы исходного диапазона. После достижения конца он возвращается к началу:

```cpp
iterator& operator++() {
    ++current_;
    if (current_ == end_) {
        current_ = begin_;
    }
    return *this;
}

decltype(auto) operator*() const {
    return *current_;
}
```

Для соответствия выбранной категории нужно определить зависимые типы и полный набор требуемых операторов.

## Адаптер и pipe-синтаксис

Для записи `range | my_views::cycle` нужен вызываемый объект-адаптер:

```cpp
struct cycle_fn {
    template <std::ranges::viewable_range R>
    auto operator()(R&& range) const {
        return cycle_view{
            std::views::all(std::forward<R>(range))
        };
    }
};

inline constexpr cycle_fn cycle;
```

В C++23 адаптер можно унаследовать от `std::ranges::range_adaptor_closure`, чтобы получить композицию через `|`.

## Подводные камни

### 1. Пустой исходный диапазон

Циклический view нельзя разыменовывать, если `begin() == end()`. Такое состояние нужно запретить или корректно обработать.

### 2. Категория итератора должна быть честной

Нельзя объявлять `bidirectional_iterator`, не реализовав все его требования или если исходный диапазон не поддерживает движение назад.

### 3. `view_interface` не реализует итератор

Он добавляет только производные операции. Основную логику `begin`, `end`, разыменования и перемещения нужно писать самостоятельно.

### 4. Следи за временем жизни

Используй `std::views::all`, чтобы корректно оборачивать lvalue и временные диапазоны.

### 5. Бесконечный view нужно ограничивать

`cycle_view` или генератор случайных чисел обычно комбинируют с `std::views::take`.

### 6. Версия стандарта важна

`std::ranges::range_adaptor_closure` появился в C++23. В C++20 оператор `|` придётся реализовать самостоятельно.

## Саммари

- Пользовательский view предоставляет `begin`, `end` и итератор.
- `view_interface` сокращает boilerplate-код.
- Наследование от него строится через CRTP.
- Бесконечный диапазон использует `std::unreachable_sentinel`.
- `std::views::all` безопасно оборачивает входной диапазон.
- Для pipe-синтаксиса нужен отдельный объект-адаптер.
