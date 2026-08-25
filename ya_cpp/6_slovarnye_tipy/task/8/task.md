# Обработка трёх токенов через `std::visit`

Перепишите `ProcessNext`, заменив последовательность `holds_alternative` и `get` одним вызовом `std::visit` для трёх токенов.

## Требования

- перед обработкой убедитесь, что в стеке есть хотя бы три токена;
- извлеките три токена из стека;
- обработайте комбинацию `Number, Operator, Number`;
- для `Plus` сложите числа, для `Minus` вычтите правое из левого;
- положите полученный `Number` обратно в стек;
- для любой другой комбинации бросьте `std::runtime_error`;
- все ветки посетителя должны иметь согласованный возвращаемый тип.

## Прекод

```cpp
#include <stack>
#include <stdexcept>
#include <variant>

enum class Operator { Plus, Minus };
enum class Bracket { Open, Close };

struct Number {
    int value;
};

using Token = std::variant<Number, Operator, Bracket>;

template <class... Ts>
struct Overloaded : Ts... {
    using Ts::operator()...;
};

template <class... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;

class TokenProcessor {
public:
    void ProcessNext() {
        if (tokens_.size() < 3) {
            throw std::runtime_error{
                "Not enough tokens for a complex token"
            };
        }

        Token first = Pop();
        Token operation = Pop();
        Token third = Pop();

        // Посетите first, operation и third одновременно.
        // Поместите результат обратно в tokens_.
    }

private:
    Token Pop() {
        Token value = std::move(tokens_.top());
        tokens_.pop();
        return value;
    }

    std::stack<Token> tokens_;
};
```

## Подсказки

- Передайте в `std::visit` три объекта после посетителя.
- Специальная лямбда принимает `const Number&`, `Operator`, `const Number&`.
- Общая лямбда принимает три `const auto&` и сообщает о неверной структуре.
- Удобно возвращать из обеих веток `Token`, а затем один раз добавить результат в стек.
- Учитывайте фактический порядок токенов при извлечении из `std::stack`.
