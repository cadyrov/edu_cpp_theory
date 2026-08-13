# Слияние отсортированных диапазонов

Реализуйте генератор `merge_sorted`, который лениво объединяет два отсортированных диапазона в одну последовательность по возрастанию.

Функция должна:

- принимать два входных диапазона с одинаковым типом элементов;
- сравнивать их текущие элементы;
- выдавать меньший элемент через `co_yield`;
- сохранить повторяющиеся значения;
- после завершения одного диапазона выдать остаток второго.

## Прекод

```cpp
#include <concepts>
#include <generator>
#include <ranges>

template <std::ranges::input_range R1,
          std::ranges::input_range R2>
requires std::same_as<
    std::ranges::range_value_t<R1>,
    std::ranges::range_value_t<R2>
>
std::generator<std::ranges::range_value_t<R1>>
merge_sorted(R1&& firstRange, R2&& secondRange) {
    auto first = std::ranges::begin(firstRange);
    auto firstEnd = std::ranges::end(firstRange);

    auto second = std::ranges::begin(secondRange);
    auto secondEnd = std::ranges::end(secondRange);

    // Ваш код здесь.
}
```

Пример:

```cpp
std::vector<int> first{1, 3, 5, 7};
std::vector<int> second{2, 3, 4, 8, 9};

for (int value : merge_sorted(first, second)) {
    std::print("{} ", value);
}

// 1 2 3 3 4 5 7 8 9
```

## Подсказка

- Пока оба диапазона не закончились, сравнивайте разыменованные итераторы.
- После `co_yield` увеличивайте итератор диапазона, из которого взят элемент.
- Затем отдельными циклами обработайте оставшиеся элементы.
- Переданные диапазоны должны существовать до завершения обхода генератора.
- `std::generator` требует C++23.
