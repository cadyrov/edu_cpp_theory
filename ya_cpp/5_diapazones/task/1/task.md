# Подсчёт элементов в отсортированном диапазоне

Вы изучили основы диапазонов и отображений — пора применить их на практике.

Реализуйте функцию `print_number_of_elements_equal_to`, которая:

- принимает отсортированный диапазон `range`, удовлетворяющий соответствующему концепту, и значение `value`;
- находит поддиапазон элементов, равных `value`;
- вызывает функцию `print_number`.

Реализуйте функцию `print_number`, которая:

- принимает отображение `view`, удовлетворяющее соответствующему концепту;
- выводит `No elements in range match the value`, если отображение пустое;
- иначе выводит количество элементов в формате `Number of elements equal to '{}' is {}`.

## Прекод

```cpp
#include <algorithm>
#include <print>
#include <ranges>
#include <set>
#include <vector>

// Здесь может быть ваш код.
void print_number(? view) {
    // Здесь ваш код.
}

// Здесь может быть ваш код.
void print_number_of_elements_equal_to(? range, ? value) {
    // Здесь ваш код.
}

int main() {
    std::multiset<int> numbers = {1, 2, 3, 3, 3, 4, 5, 7, 8, 9};
    print_number_of_elements_equal_to(numbers, 3);
    print_number_of_elements_equal_to(numbers, 13);

    std::vector<double> vec{1.1, 2.2, 3.3, 3.3, 4.4, 5.5, 7.7, 8.8, 9.9};
    print_number_of_elements_equal_to(vec, 3.3);
}
```

Ожидаемый вывод:

```text
Number of elements equal to '3' is 3
No elements in range match the value
Number of elements equal to '3.3' is 2
```

## Подсказка

- Используйте концепты `std::ranges::range` и `std::ranges::view`.
- Используйте `std::equal_range` для поиска границ равных элементов.
- Создайте отображение границ с помощью `std::ranges::subrange`.
