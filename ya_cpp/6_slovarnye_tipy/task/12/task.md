# Очередь произвольных сообщений

Допишите `MessageQueue`, которая хранит сообщения разных копируемых типов в одном контейнере.

## Требования

- `messages_` хранит объекты `std::any`;
- `AddMessage` принимает сообщение произвольного копируемого типа;
- сообщение помещается в контейнер с корректной передачей значения;
- `Show` выводит диагностическое имя фактического типа каждого сообщения;
- добавьте в очередь `TextMessage` и `StatusMessage`.

## Прекод

```cpp
#include <any>
#include <print>
#include <type_traits>
#include <utility>
#include <vector>

struct TextMessage {};
struct ImageMessage {};
struct StatusMessage {};

class MessageQueue {
public:
    template <typename T>
    requires std::copy_constructible<std::decay_t<T>>
    void AddMessage(T&& message) {
        // Ваш код здесь.
    }

    void Show() const {
        for (const std::any& message : messages_) {
            std::println("{}", message.type().name());
        }
    }

private:
    // Добавьте контейнер messages_ здесь.
};

int main() {
    MessageQueue queue;

    queue.AddMessage(TextMessage{});
    queue.AddMessage(StatusMessage{});
    queue.Show();
}
```

## Подсказки

- Добавьте `#include <concepts>`.
- Используйте `std::vector<std::any>`.
- Передавайте аргумент в `emplace_back` через `std::forward<T>`.
- `type().name()` зависит от реализации и подходит здесь только для диагностики.
