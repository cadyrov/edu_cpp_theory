# Индекс событий по энергии

Дан массив событий Самого Маленького Адронного Коллайдера:

```cpp
struct ParticleEvent {
    unsigned event_id;
    double total_energy;
};
```

Реализуйте функцию `buildIndex`, которая возвращает индексы элементов `events` в порядке убывания `total_energy`.

Исходный вектор событий изменять нельзя.

## Прекод

```cpp
#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>

struct ParticleEvent {
    unsigned event_id;
    double total_energy; // ГэВ
};

std::vector<std::size_t> buildIndex(
    const std::vector<ParticleEvent>& events
) {
    std::vector<std::size_t> indices(events.size());
    std::ranges::iota(indices, 0);

    std::ranges::sort(indices, /* Ваш код здесь */);

    return indices;
}
```

## Подсказка

- Сортируйте вектор индексов через `std::ranges::sort`.
- Используйте `std::ranges::greater` для порядка по убыванию.
- Проекция должна превращать индекс в энергию соответствующего события.
- `std::ranges::iota` требует C++23.
