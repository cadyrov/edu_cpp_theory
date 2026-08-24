# 10. Функциональный объект `std::function`

## Суть

В C++ вызываемым объектом может быть:

- обычная функция или указатель на неё;
- лямбда;
- функтор с `operator()`;
- результат `std::bind`;
- другой совместимый callable.

У каждого callable свой тип. `std::function<R(Args...)>` стирает этот тип и оставляет единый копируемый интерфейс вызова.

```cpp
#include <functional>

std::function<int(int, int)> operation;

operation = [](int lhs, int rhs) {
    return lhs + rhs;
};

int result = operation(2, 3); // 5
```

`std::function` появился в C++11.

## Что можно хранить

```cpp
int Add(int lhs, int rhs) {
    return lhs + rhs;
}

struct Multiply {
    int operator()(int lhs, int rhs) const {
        return lhs * rhs;
    }
};

std::function<int(int, int)> first = Add;
std::function<int(int, int)> second = Multiply{};
std::function<int(int, int)> third =
    [](int lhs, int rhs) { return lhs - rhs; };
```

Объект должен быть вызываем с аргументами объявленной сигнатуры, а результат — совместим с `R`.

## Основные применения

### Callback

```cpp
class Button {
public:
    void SetHandler(std::function<void()> handler) {
        handler_ = std::move(handler);
    }

    void Click() const {
        if (handler_) {
            handler_();
        }
    }

private:
    std::function<void()> handler_;
};
```

### Очередь задач

```cpp
std::vector<std::function<void()>> tasks;

tasks.push_back([] { Save(); });
tasks.push_back([] { Send(); });

for (const auto& task : tasks) {
    task();
}
```

### Стратегия

```cpp
using Comparator = std::function<bool(const Item&, const Item&)>;
```

`std::function` особенно полезен, если callable нужно хранить, копировать, заменять во время выполнения или помещать в однородный контейнер.

## Пустое состояние

```cpp
std::function<void()> callback;

if (callback) {
    callback();
}
```

Вызов пустого `std::function` бросает `std::bad_function_call`.

```cpp
callback = nullptr;
bool empty = (callback == nullptr);
```

Сравнивать два `std::function` по смыслу хранимых функций нельзя.

## Как работает type erasure

Концептуально `std::function` хранит:

- сам callable или указатель на него;
- функцию вызова;
- операции копирования, перемещения и уничтожения;
- информацию о фактическом типе, скрытую от пользователя интерфейса.

Упрощённая схема:

```cpp
struct CallableBase {
    virtual int Invoke(int) = 0;
    virtual std::unique_ptr<CallableBase> Clone() const = 0;
    virtual ~CallableBase() = default;
};

template <typename F>
struct Callable final : CallableBase {
    F function;

    int Invoke(int value) override {
        return function(value);
    }

    std::unique_ptr<CallableBase> Clone() const override {
        return std::make_unique<Callable>(*this);
    }
};
```

Реальная стандартная библиотека не обязана использовать виртуальное наследование: детали реализации не стандартизованы.

## Small-object optimization

Многие реализации имеют небольшой внутренний буфер:

- маленький callable хранится внутри `std::function`;
- большой callable обычно требует динамической аллокации.

```cpp
struct SmallTask {
    int value;
    void operator()() const;
};

struct BigTask {
    std::array<std::byte, 128> data;
    void operator()() const;
};
```

Порог SBO, требования к выравниванию и выбор размещения зависят от реализации. Нельзя переносимо определять наличие аллокации только по `sizeof(callable)`.

## Ограничение копируемости

Целевой объект `std::function` должен быть копируемым. Move-only лямбда не подходит:

```cpp
auto task = [value = std::make_unique<int>(42)] {
    Use(*value);
};

// std::function<void()> function = std::move(task); // ошибка
```

Сам `std::function` можно и копировать, и перемещать, но перемещение обёртки не снимает требование копируемости цели.

## `std::move_only_function`

В C++23 появился владеющий move-only аналог:

```cpp
std::move_only_function<void()> function = std::move(task);
function();
```

Он подходит для одноразовых задач, обработчиков с `unique_ptr`, сокетов и других некопируемых ресурсов.

## `std::copyable_function` и `std::function_ref`

В C++26 семейство обёрток расширяется:

- `std::copyable_function` — копируемая владеющая обёртка с поддержкой `const`, ref- и `noexcept`-квалифицированных сигнатур;
- `std::function_ref` — лёгкая невладеющая ссылка на callable.

### Сравнение обёрток

| Тип | Стандарт | Владеет callable | Копируется | Хранит move-only цель | Квалификаторы сигнатуры |
|---|---:|---:|---:|---:|---:|
| `std::function` | C++11 | Да | Да | Нет | Ограниченно |
| `std::move_only_function` | C++23 | Да | Нет | Да | `cv`, ref, `noexcept` |
| `std::copyable_function` | C++26 | Да | Да | Нет | `cv`, ref, `noexcept` |
| `std::function_ref` | C++26 | Нет | Да | Не хранит объект | `cv`, ref, `noexcept` |

`function_ref` требует, чтобы исходный callable жил дольше обёртки.

## `std::function` или шаблон

```cpp
template <typename F>
void Repeat(int count, F&& function) {
    for (int i = 0; i < count; ++i) {
        std::invoke(function, i);
    }
}
```

| Критерий | Шаблонный callable | `std::function` |
|---|---|---|
| Хранение разных типов в одном контейнере | Нет напрямую | Да |
| Возможность inline | Высокая | Ограничена косвенным вызовом |
| Аллокация | Обычно нет | Возможна |
| Время компиляции | Отдельная инстанциация для типа | Стабильный внешний интерфейс |
| ABI и сокрытие реализации | Тип callable виден | Тип стёрт |
| Move-only callable | Да | Нет |

Если функция лишь сразу вызывает переданный обработчик и не хранит его, шаблон часто проще и быстрее. Для стабильного хранимого callback type erasure удобнее.

## Перегруженные и обобщённые функции

Перегруженное имя нужно разрешить явно:

```cpp
void Print(int);
void Print(double);

std::function<void(int)> function =
    static_cast<void (*)(int)>(Print);
```

Лямбда-обёртка обычно читается проще:

```cpp
std::function<void(int)> function = [](int value) {
    Print(value);
};
```

Обобщённую лямбду можно хранить, но `std::function` фиксирует одну конкретную сигнатуру:

```cpp
auto twice = [](auto value) { return value * 2; };

std::function<int(int)> ints = twice;
std::function<double(double)> doubles = twice;
```

Типа `std::function<auto(auto)>` не существует.

## Подводные камни

### 1. Захваты по ссылке могут стать висячими

```cpp
std::function<void()> MakeTask() {
    std::string local = "data";
    return [&local] { Use(local); }; // dangling reference
}
```

Для долгоживущего callback продумывайте владение захваченными объектами.

### 2. Вызов не бесплатен

Type erasure добавляет косвенный вызов, а крупная цель может вызвать аллокацию. В горячем коде измеряйте и сравнивайте с шаблоном.

### 3. Передача `std::function` не всегда избавляет от создания обёртки

При вызове функции, принимающей `const std::function<...>&`, из лямбды сначала создаётся временный `std::function`. Если обработчик не сохраняется, рассмотрите шаблон или невладеющий `function_ref`.

### 4. Проверяйте пустое состояние

Пустой `std::function` бросает исключение при вызове. Для `move_only_function` и `copyable_function` вызов без цели нарушает предусловие.

### 5. `std::bind` часто менее прозрачен, чем лямбда

Лямбды лучше выражают захваты, типы и порядок аргументов и обычно проще диагностируются.

### 6. SBO не гарантирует отсутствие аллокации для произвольной цели

Результат зависит от размера, выравнивания, свойств перемещения и реализации библиотеки.

## Саммари

- `std::function<R(Args...)>` — копируемая владеющая type-erased обёртка.
- Она хранит разные callable с одной совместимой сигнатурой.
- Пустой `std::function` бросает `std::bad_function_call` при вызове.
- Хранимая цель должна быть копируемой.
- SBO часто избавляет маленькие цели от аллокации, но его порог не стандартизован.
- Для move-only целей используйте `std::move_only_function` из C++23.
- В C++26 доступны `copyable_function` и невладеющий `function_ref`.
- Если callable не нужно хранить, шаблон часто предпочтительнее.
