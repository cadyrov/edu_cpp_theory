# Реестр запросов к базам данных

Разработайте контейнер, который по строковому имени базы хранит и запускает запрос.

`Request` перемещаемый, но не копируемый, поэтому обычный `std::function` для него не подходит.

## Требования

- ключ контейнера — `std::string`;
- значение — type-erased callable с сигнатурой `Response()`;
- callable должен поддерживать move-only объекты;
- добавьте `Request` под ключом `"db1"`;
- вызовите запрос через `at("db1")` и выведите поле `data`;
- используйте C++23.

## Прекод

```cpp
#include <functional>
#include <print>
#include <string>
#include <unordered_map>
#include <utility>

struct Response {
    std::string data;
};

struct Request {
    std::string data;

    Request() = default;
    Request(Request&&) = default;
    Request& operator=(Request&&) = default;

    Request(const Request&) = delete;
    Request& operator=(const Request&) = delete;

    Response operator()() {
        std::println("Process request: {}", data);
        return {.data = "Result"};
    }
};

int main() {
    // Объявите unordered_map со строковым ключом
    // и move-only функциональной обёрткой.

    Request request;
    request.data = "SELECT * FROM users";

    // Переместите request в requests["db1"].

    std::println("{}", requests.at("db1")().data);
}
```

## Подсказки

- Используйте `std::move_only_function<Response()>`.
- Тип контейнера: `std::unordered_map<std::string, ...>`.
- Передайте `request` через `std::move`.
- После перемещения не рассчитывайте на прежнее содержимое `request`.
