# Минимум и максимум через `fold_left`

Реализуйте функцию `find_min_max_values`, которая за один проход находит минимальный и максимальный элементы диапазона с помощью `std::ranges::fold_left`.

Если диапазон пуст, функция должна выбросить `std::invalid_argument`.

## Прекод

```cpp
#include <algorithm>
#include <limits>
#include <ranges>
#include <stdexcept>
#include <utility>

template <std::ranges::input_range R>
requires std::numeric_limits<
    std::ranges::range_value_t<R>
>::is_specialized
auto find_min_max_values(R&& range) {
    if (std::ranges::empty(range)) {
        throw std::invalid_argument(
            "find_min_max_values called with an empty range."
        );
    }

    using T = std::ranges::range_value_t<R>;
    using State = std::pair<T, T>;

    State initial{
        std::numeric_limits<T>::max(),
        std::numeric_limits<T>::lowest()
    };

    auto update = /* Ваш код здесь */;

    return std::ranges::fold_left(range, initial, update);
}
```

## Подсказка

- Лямбда принимает текущее состояние `State` и очередной элемент диапазона.
- Первый компонент состояния — минимум, второй — максимум.
- Возвращайте новое состояние с учётом очередного элемента.
- Используйте `std::min` и `std::max`.
- `std::ranges::fold_left` требует C++23.
