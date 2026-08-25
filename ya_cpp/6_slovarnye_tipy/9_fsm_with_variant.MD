# 9. Конечный автомат на `std::variant`

## Суть

Конечный автомат (FSM) описывается тремя частями:

- состояния — в каком этапе находится система;
- события — что произошло;
- переходы — новое состояние для пары `{текущее состояние, событие}`.

В каждый момент активно ровно одно состояние, поэтому его удобно хранить в `std::variant`. События также образуют закрытый набор типов, а `std::visit` выполняет двойную диспетчеризацию.

```cpp
using State = std::variant<Idle, Running, Finished>;
using Event = std::variant<Start, Complete, Reset>;

state = std::visit(Transition{}, state, event);
```

## Проблемы подхода `enum + общие поля`

```cpp
enum class State {
    Initiated,
    Pending,
    Completed,
    Failed
};
```

Один большой класс обычно хранит поля сразу для всех состояний:

```cpp
std::optional<std::string> transactionId;
std::optional<std::string> receipt;
std::optional<std::string> failureReason;
```

Недостатки:

- возможны бессмысленные сочетания флага состояния и заполненных полей;
- данные разных этапов смешиваются;
- события приходится сопровождать универсальным `Params` с необязательными полями;
- допустимость перехода проверяется вручную в большом `switch`.

## Состояния как отдельные типы

Каждое состояние хранит только актуальные данные:

```cpp
namespace state {

struct Initiated {
    double amount;
    std::string recipient;
    std::string sender;
};

struct AwaitingClearance {
    std::string transactionId;
};

struct Completed {
    std::string transactionId;
    std::string receipt;
};

struct Failed {
    std::string transactionId;
    std::string reason;
};

} // namespace state

using TransferState = std::variant<
    state::Initiated,
    state::AwaitingClearance,
    state::Completed,
    state::Failed
>;
```

Нельзя случайно прочитать `receipt` у незавершённого перевода: такого поля в соответствующем типе просто нет.

## События как отдельные типы

```cpp
namespace event {

struct Send {
    std::string transactionId;
};

struct Approve {
    std::string receipt;
};

struct Reject {
    std::string reason;
};

} // namespace event

using TransferEvent = std::variant<
    event::Send,
    event::Approve,
    event::Reject
>;
```

В отличие от `enum Event + Params`, каждый тип события требует только собственные данные.

## Таблица переходов

| Текущее состояние | Событие | Следующее состояние |
|---|---|---|
| `Initiated` | `Send` | `AwaitingClearance` |
| `AwaitingClearance` | `Approve` | `Completed` |
| `AwaitingClearance` | `Reject` | `Failed` |
| Остальные пары | — | Ошибка перехода |

Такая таблица должна быть источником истины для посетителя и тестов.

## Посетитель переходов

```cpp
struct Transition {
    TransferState operator()(
        const state::Initiated& current,
        const event::Send& next
    ) const {
        LogAmount(current.amount);
        return state::AwaitingClearance{next.transactionId};
    }

    TransferState operator()(
        const state::AwaitingClearance& current,
        const event::Approve& next
    ) const {
        return state::Completed{
            current.transactionId,
            next.receipt
        };
    }

    TransferState operator()(
        const state::AwaitingClearance& current,
        const event::Reject& next
    ) const {
        return state::Failed{
            current.transactionId,
            next.reason
        };
    }

    TransferState operator()(const auto&, const auto&) const {
        throw std::logic_error{"Unsupported transition"};
    }
};
```

Каждая перегрузка кодирует одну допустимую пару типов. Общая перегрузка обрабатывает остальные комбинации.

## Обёртка автомата

```cpp
class TransferMachine {
public:
    explicit TransferMachine(state::Initiated initial)
        : state_(std::move(initial)) {}

    void Process(const TransferEvent& event) {
        state_ = std::visit(Transition{}, state_, event);
    }

    const TransferState& CurrentState() const {
        return state_;
    }

private:
    TransferState state_;
};
```

Логику переходов лучше держать чистой: посетитель получает состояние и событие, проверяет инварианты и возвращает новое состояние.

## Данные состояния и общий контекст

При переходе старый объект состояния уничтожается. Данные, нужные на следующих этапах, необходимо:

- явно перенести в новое состояние;
- либо хранить в общем контексте автомата.

```cpp
struct TransferContext {
    double amount;
    std::string sender;
    std::string recipient;
};
```

Это особенно важно для аудита, повторных попыток и временного перехода в состояние обработки инцидента.

## Самопереходы и игнорирование событий

Недопустимая пара не всегда является ошибкой. Возможны три политики:

```cpp
// Ошибка.
throw std::logic_error{"Unsupported transition"};

// Состояние не меняется.
return current;

// Явный результат с ошибкой.
return std::unexpected(TransitionError{...});
```

Политику следует определить в диаграмме переходов, а не выбирать случайно внутри обработчика.

## Отчёт о текущем состоянии

`typeid(value).name()` возвращает implementation-defined имя. Для пользовательского вывода лучше явный посетитель:

```cpp
std::string_view StateName(const TransferState& state) {
    return std::visit(Overloaded{
        [](const state::Initiated&) {
            return std::string_view{"Initiated"};
        },
        [](const state::AwaitingClearance&) {
            return std::string_view{"AwaitingClearance"};
        },
        [](const state::Completed&) {
            return std::string_view{"Completed"};
        },
        [](const state::Failed&) {
            return std::string_view{"Failed"};
        }
    }, state);
}
```

## Сравнение реализаций FSM

| Критерий | `enum + switch` | `variant + visit` |
|---|---|---|
| Данные состояния | Часто собраны в одном классе | Локализованы в типе состояния |
| Данные события | Часто общий `Params` | Отдельный тип события |
| Недопустимые поля | Возможны | Многие исключаются структурой типов |
| Переходы | Вложенные `switch` | Перегрузки по паре типов |
| Добавление состояния | Меняет enum и switch | Меняет variant и посетителей |
| Размер объекта | Все общие поля | Крупнейшее состояние плюс индекс |
| Открытый набор состояний | Нет | Нет |

## Подводные камни

### 1. Catch-all переносит проверку на runtime

С общей перегрузкой посетитель компилируется для любого нового состояния или события. Забытый переход обнаружится только при выполнении.

### 2. `variant` не запрещает логически неверный переход автоматически

Посетитель всё ещё может вернуть любое состояние. Корректность таблицы переходов проверяется дизайном и тестами.

### 3. Не теряйте данные при переходе

Если временное состояние инцидента не хранит предыдущее состояние или нужный контекст, восстановить процесс без потерь невозможно.

### 4. Исключение — не состояние автомата

Если отказ является частью бизнес-процесса, лучше моделировать его типом `Failed` или результатом `expected`, а не считать исключение нормальным конечным состоянием.

### 5. Добавление типа затрагивает матрицу переходов

Нужно обновить `variant`, посетителя, отчёт о состоянии, сериализацию и тесты.

### 6. Побочные эффекты усложняют надёжность

Если обработчик сначала отправил запрос наружу, а затем не смог создать новое состояние, система может стать несогласованной. Отделяйте вычисление перехода от выполнения команд.

### 7. Производительность нужно измерять

`variant` часто хорошо подходит по размещению данных, но не гарантирует скорость, равную `enum + switch`, для любого набора состояний.

## Саммари

- FSM состоит из состояний, событий и таблицы переходов.
- `variant<State...>` гарантирует одно активное состояние.
- Отдельные структуры локализуют данные каждого состояния и события.
- `visit(Transition{}, state, event)` выбирает переход по двум активным типам.
- Недопустимые переходы можно отклонять, игнорировать или возвращать как явную ошибку.
- Общие данные и данные для возврата из временного состояния нельзя терять.
- Новые состояния требуют обновления всей матрицы переходов и связанных обработчиков.
