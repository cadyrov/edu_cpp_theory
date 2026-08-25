# Сообщения авторизации через `std::expected`

Сформируйте сообщение для каждой пары логина и пароля с помощью монадического интерфейса.

## Требования

- вызовите `TryLogin`, возвращающую `std::expected<User, LoginError>`;
- через `transform` создайте строку `"Welcome, {display_name}"`;
- через `or_else` замените ошибку строкой `"Login failed: {описание}"`;
- извлеките итоговую строку только после полного восстановления ошибки;
- переместите сообщение в `loginMessages`;
- не используйте явные `if` внутри цикла.

## Прекод

```cpp
#include <expected>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

enum class LoginError {
    InvalidPassword,
    UserNotFound,
    ConnectionFailed
};

struct User {
    std::string display_name;
};

std::expected<User, LoginError>
TryLogin(std::string_view username, std::string_view password);

std::string DescribeError(LoginError error);

int main() {
    std::vector<std::pair<std::string, std::string>> credentials{
        {"username", "password"}
    };

    std::vector<std::string> loginMessages;

    for (const auto& [username, password] : credentials) {
        // Ваш код здесь.
    }
}
```

## Подсказки

- После `transform` тип равен `std::expected<std::string, LoginError>`.
- Callback `or_else` принимает `LoginError`.
- Для восстановления верните успешный `std::expected<std::string, LoginError>`.
- После такого `or_else` обе исходные ветки содержат значение, поэтому допустим вызов `value()`.
- Используйте `std::move(message)` при добавлении строки в вектор.
