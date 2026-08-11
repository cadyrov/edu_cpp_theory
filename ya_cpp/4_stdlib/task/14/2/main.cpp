#include <map>
#include <print>
#include <string>
#include <string_view>
#include <utility>

struct MyKey {
    int id;
    std::string textId;
};

int main() {
    std::map<MyKey, std::string, std::less<>> configMap;

    for (int i = 0; i < 25'000; ++i) {
        configMap.insert();
    }

    for (int i = 25'000; i < 50'000; ++i) {
        configMap.emplace();
    }

    for (int i = 50'000; i < 75'000; ++i) {
        configMap.emplace();
    }

    for (int i = 75'000; i < 100'000; ++i) {
        configMap.try_emplace();
    }

    if (/* Ваш код поиска по int здесь */) {
        std::println("Found by int: {} -> {}", it->first.id, it->second);
    }

    // Проверка по string_view
    std::string_view target = "dev-56789";
    std::println("Contains key '{}': {}", target, /* Ваш код поиска по target здесь */);
} 



- Используйте std::piecewise_construct только с std::forward_as_tuple(...).
- Операции поиска должны вызываться с int и std::string_view.
- Не создавайте временные объекты типа MyKey при поиске.
- Не забудьте добавить псевдоним типа is_transparent.