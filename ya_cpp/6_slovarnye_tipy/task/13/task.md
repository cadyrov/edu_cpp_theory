# Загрузка игровой конфигурации через `std::expected`

Реализуйте загрузку и разбор конфигурации без исключений, возвращая значение либо текст ошибки.

## Требования

### `LoadFile`

- возвращает `std::expected<std::string, std::string>`;
- для пути, отличного от `"config.cfg"`, возвращает `std::unexpected` с сообщением;
- для корректного пути вызывает `ReadFile`.

### `ParseConfig`

- возвращает `std::expected<Config, std::string>`;
- проверяет префикс `"GameCfg:"`;
- при неверном префиксе возвращает текст ошибки;
- записывает в `key` символы диапазона `[590, 600)`;
- записывает в `value` символы диапазона `[601, 610)`;
- проверяет достаточную длину входных данных;
- создаёт `Config` внутри `expected` через `std::in_place`.

### `main`

- после каждого вызова проверяет результат;
- печатает ошибку и возвращает `1` при неуспехе;
- при успехе выводит `key` и `value`.

## Прекод

```cpp
#include <array>
#include <cstddef>
#include <expected>
#include <print>
#include <string>
#include <string_view>
#include <utility>

struct Config {
    Config(std::string keyValue, std::string storedValue)
        : key(std::move(keyValue)),
          value(std::move(storedValue)) {}

    std::string key;
    std::string value;
    std::array<std::byte, 1024> metadata{};
};

std::string ReadFile(std::string_view path) {
    std::string content(16'384, 'A');
    content.replace(0, 8, "GameCfg:");
    return content;
}

[[nodiscard]]
std::expected<std::string, std::string>
LoadFile(std::string_view path) {
    // Ваш код здесь.
}

[[nodiscard]]
std::expected<Config, std::string>
ParseConfig(std::string_view content) {
    // Ваш код здесь.
}

int main() {
    auto content = LoadFile("config.cfg");
    // При ошибке напечатайте content.error() и верните 1.

    auto config = ParseConfig(*content);
    // При ошибке напечатайте config.error() и верните 1.

    // Выведите config->key и config->value.
    return 0;
}
```

## Подсказки

- Ошибка: `return std::unexpected{std::string{"message"}};`.
- Для `std::string` достаточно вернуть результат `ReadFile` напрямую.
- Проверить префикс можно через `starts_with`.
- Диапазон `[first, last)` имеет длину `last - first`.
- Создание на месте: `std::expected<Config, std::string>{std::in_place, key, value}`.
- Сначала проверяйте `expected`, только затем используйте `*` или `->`.
