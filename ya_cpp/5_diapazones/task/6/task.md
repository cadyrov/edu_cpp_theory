# Разбиение строки на слова

Дана строка:

```cpp
std::string text = "C++ Ranges are powerful";
```

Получите объект `words` типа `std::vector<std::string>`, содержащий отдельные слова.

Нужно:

- разделить исходную строку по пробелам;
- преобразовать каждый диапазон символов в `std::string`;
- материализовать диапазон строк в `std::vector<std::string>`.

## Прекод

```cpp
#include <ranges>
#include <string>
#include <vector>

int main() {
    std::string text = "C++ Ranges are powerful";

    auto words = /* Ваш код здесь */;
}
```

Ожидаемое содержимое `words`:

```text
C++
Ranges
are
powerful
```

## Подсказка

- Используйте `std::views::split(' ')`.
- Преобразуйте каждую часть через `std::ranges::to<std::string>`.
- Весь результат преобразуйте через `std::ranges::to<std::vector>()`.
- `std::ranges::to` требует C++23.
