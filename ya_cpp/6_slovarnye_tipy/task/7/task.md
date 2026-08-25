# Практика с `std::visit`

## Задание 1. Overloaded-посетитель

Перепишите `Print` с помощью паттерна Overloaded.

Требования:

- для `std::string`, `double` и `int` используйте отдельные лямбды;
- выводите `Получен {тип}: {значение}`;
- добавьте обобщённую ветку, бросающую `std::logic_error` для неподдерживаемого типа;
- используйте `variant::visit` из C++26.

```cpp
#include <stdexcept>
#include <string>
#include <variant>

template <class... Ts>
struct Overloaded : Ts... {
    using Ts::operator()...;
};

void Print(std::variant<std::string, double, int> value) {
    // Ваш код здесь.
}
```

Для C++17–23 дополнительно реализуйте тот же вызов через `std::visit`.

## Задание 2. Вычислитель выражений

Реализуйте вычисление выражений с `+`, `-` и скобками. Токен представлен типом-суммой:

```cpp
using Token = std::variant<Number, Operator, Bracket>;
```

### Требования

1. Реализуйте все методы `TokenStream`.
2. В `Tokenize` удалите пробелы, сгруппируйте цифры, преобразуйте группы в токены и соберите `std::deque<Token>`.
3. В `EvaluateTokensWithoutBrackets` последовательно применяйте `+` и `-`.
4. В `Evaluate` сворачивайте выражения от ближайшей закрывающей скобки до соответствующей открывающей.
5. При неожиданном типе токена бросайте `std::runtime_error`.

### Прекод

```cpp
#include <charconv>
#include <cctype>
#include <deque>
#include <format>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>

enum class Operator { Plus, Minus };
enum class Bracket { Open, Close };

struct Number {
    int value;
};

namespace rng = std::ranges;
namespace views = std::ranges::views;

using Token = std::variant<Number, Operator, Bracket>;

class TokenStream {
public:
    explicit TokenStream(std::deque<Token> tokens)
        : tokens_(std::move(tokens)) {}

    bool empty() const {
        // Ваш код здесь.
    }

    Number NextNumber() {
        // Ваш код здесь.
    }

    Operator NextOp() {
        // Ваш код здесь.
    }

    bool IsNextBracketOpen() const {
        // Ваш код здесь.
    }

    bool IsNextBracketClose() const {
        // Ваш код здесь.
    }

    Token pop() {
        // Ваш код здесь.
    }

    void push_front(Token token) {
        // Ваш код здесь.
    }

    bool HasNext() const {
        // Ваш код здесь.
    }

    Token front() const {
        // Ваш код здесь.
    }

private:
    std::deque<Token> tokens_;
};

std::deque<Token> Tokenize(std::string_view input) {
    auto isDigit = [](char value) {
        return std::isdigit(static_cast<unsigned char>(value));
    };

    auto toToken = [&](auto&& chunk) -> Token {
        const std::string text(chunk.begin(), chunk.end());
        const char first = text.front();

        switch (first) {
        case '+': return Operator::Plus;
        case '-': return Operator::Minus;
        case '(': return Bracket::Open;
        case ')': return Bracket::Close;
        }

        if (isDigit(first)) {
            int value{};
            const auto [ptr, error] = std::from_chars(
                text.data(), text.data() + text.size(), value
            );
            if (error == std::errc{} && ptr == text.data() + text.size()) {
                return Number{value};
            }
            throw std::runtime_error{
                std::format("Invalid number: '{}'", text)
            };
        }

        throw std::runtime_error{
            std::format("Unexpected character: {}", first)
        };
    };

    return input
        | /* filter пробелов */
        | /* chunk_by для цифр */
        | /* transform в Token */
        | /* ranges::to<deque<Token>> */;
}

Number EvaluateTokensWithoutBrackets(TokenStream stream) {
    Number result = stream.NextNumber();

    while (stream.HasNext() && !stream.IsNextBracketClose()) {
        // Ваш код здесь.
    }

    return result;
}

Number Evaluate(TokenStream stream) {
    std::deque<Token> stack;

    while (stream.HasNext()) {
        if (stream.IsNextBracketClose()) {
            stream.pop();
            std::deque<Token> inner;

            // Перенесите токены до открывающей скобки в inner.

            Number reduced = EvaluateTokensWithoutBrackets(
                TokenStream{std::move(inner)}
            );
            stack.emplace_back(reduced);
        } else {
            stack.push_back(stream.pop());
        }
    }

    return EvaluateTokensWithoutBrackets(
        TokenStream{std::move(stack)}
    );
}
```

Ожидаемый результат для выражения:

```text
1 + 2 - (3 + 4 - (5 - 6)) + 7
```

```text
Result = 2
```

### Подсказки

- Проверяйте тип через `std::holds_alternative`, извлекайте через `std::get`.
- Для токенизации используйте `views::filter`, `views::chunk_by`, `views::transform` и `ranges::to`.
- Из стека переносите токены в начало `inner`, чтобы сохранить порядок.
- Проверяйте несбалансированные скобки и неожиданный конец потока.
- Используемые ranges-возможности требуют C++23.
