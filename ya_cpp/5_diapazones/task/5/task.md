# Бесконечное отображение случайных чисел

Реализуйте пользовательское отображение `views::random`, которое генерирует бесконечную последовательность случайных целых чисел.

Нужно:

- определить поля `random_view` по сценариям использования;
- реализовать параметризованный конструктор отображения;
- определить состояние и конструктор итератора;
- реализовать разыменование, инкременты и сравнение;
- реализовать `begin()` и `end()`;
- добавить фабричную функцию `random`;
- поддержать pipe-синтаксис;
- обеспечить одинаковые последовательности для одинаковых границ и `seed`.

## Прекод

```cpp
#include <concepts>
#include <cstddef>
#include <print>
#include <random>
#include <ranges>

namespace views {

template <std::integral IntType>
class random_view
    : public std::ranges::view_interface<random_view<IntType>> {
public:
    random_view() = default;

    // Параметризованный конструктор отображения.

    class iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = IntType;
        using difference_type = std::ptrdiff_t;
        using pointer = const IntType*;
        using reference = const IntType&;

        iterator() = default;

        // Параметризованный конструктор итератора.

        value_type operator*() const {
            // Ваш код здесь.
        }

        iterator& operator++() {
            // Ваш код здесь.
        }

        iterator operator++(int) {
            // Ваш код здесь.
        }

        constexpr bool operator==(const iterator& other) const {
            // Ваш код здесь.
        }

        constexpr bool operator==(
            std::unreachable_sentinel_t
        ) const {
            // Ваш код здесь.
        }

    private:
        // Поля итератора.
    };

    auto begin() {
        // Ваш код здесь.
    }

    auto end() {
        // Ваш код здесь.
    }

private:
    // Поля отображения.
};

template <std::integral T>
auto random(T a, T b, T seed = std::random_device{}()) {
    // Ваш код здесь.
}

// Перегрузка operator| для pipe-синтаксиса.

}  // namespace views
```

## Проверка

```cpp
int main() {
    for (int number : views::random(1, 100)
                        | std::views::take(5)) {
        std::print("{} ", number);
    }
    std::println();

    for (int number : std::views::iota(0)
                        | views::random(1, 100, 0)
                        | std::views::take(5)) {
        std::print("{} ", number);
    }
    std::println();

    for (int number : views::random_view(1, 100, 42)
                        | std::views::take(5)) {
        std::print("{} ", number);
    }
}
```

## Подсказка

- Используйте генератор, которому можно передать `seed`, и распределение целых чисел.
- Конец бесконечного диапазона обозначается `std::unreachable_sentinel`.
- Одинаковый `seed` должен создавать одинаковое начальное состояние генератора.
- В двустороннем pipe-синтаксисе левый диапазон используется только как синтаксическая основа и не влияет на генерируемые значения.
