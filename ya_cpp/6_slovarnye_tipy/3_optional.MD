# 3. `std::optional`

## Суть

`std::optional<T>` хранит либо значение типа `T`, либо состояние «значения нет». Тип появился в C++17 и заменяет:

- магические значения вроде `-1`;
- пару `{value, success}`;
- отдельный `bool`-флаг рядом с объектом;
- обязательное создание объекта до момента, когда он понадобится.

```cpp
#include <optional>

std::optional<int> Find(bool found) {
    if (!found) {
        return std::nullopt;
    }
    return 42;
}
```

`optional` подходит, когда отсутствие результата нормально и не требует описания причины ошибки.

## Создание и проверка

```cpp
std::optional<int> empty;
std::optional<int> alsoEmpty = std::nullopt;
std::optional<int> value = 42;

if (value.has_value()) {
    // значение есть
}

if (value) { // то же самое
    // значение есть
}

value = 100;
value.reset();          // очистить
value = std::nullopt;   // тоже очистить
value.emplace(200);     // создать T непосредственно внутри optional
```

## Доступ к значению

```cpp
std::optional<std::string> name = "Alice";

std::string a = name.value();
std::string b = name.value_or("Unknown");
std::size_t size = name->size();
const std::string& ref = *name;
```

- `value()` проверяет состояние и бросает `std::bad_optional_access`, если значения нет;
- `*opt` и `opt->` не проверяют состояние;
- `value_or(fallback)` возвращает значение либо запасной вариант.

## Возврат из функции

```cpp
#include <charconv>
#include <optional>
#include <string_view>

std::optional<int> ParseInt(std::string_view text) {
    int value{};
    const auto [ptr, error] =
        std::from_chars(text.data(), text.data() + text.size(), value);

    if (error != std::errc{} || ptr != text.data() + text.size()) {
        return std::nullopt;
    }
    return value;
}
```

Вызывающий код обязан явно обработать отсутствие значения:

```cpp
if (auto value = ParseInt("42")) {
    Use(*value);
}
```

## Ленивая инициализация

```cpp
class UserProfile {
public:
    const ProfileData& GetProfile() {
        if (!profile_) {
            profile_.emplace(FetchProfile());
        }
        return *profile_;
    }

private:
    std::optional<ProfileData> profile_;
};
```

Объект `ProfileData` создаётся только при первом обращении. Отдельный флаг не нужен.

## Как устроен `optional`

Концептуально `optional<T>` содержит:

- память, достаточную для размещения `T`;
- флаг, показывающий, создан ли объект в этой памяти.

Пустой `optional<T>` не создаёт `T`, но память под него уже входит в размер `optional`. Конкретная реализация через `union` и внутренние базовые классы зависит от стандартной библиотеки.

## Перемещение и создание на месте

`value_or` имеет перегрузки для lvalue и rvalue. Из временного `optional` значение можно переместить:

```cpp
std::string value = MakeName().value_or("Unknown");
```

При преобразовании `T` в `optional<T>` создаётся новый объект внутри `optional`. Для неперемещаемого типа лучше использовать `std::in_place`:

```cpp
struct NonMovable {
    NonMovable() = default;
    NonMovable(const NonMovable&) = delete;
    NonMovable(NonMovable&&) = delete;
};

std::optional<NonMovable> Create() {
    return std::optional<NonMovable>{std::in_place};
}
```

## Подводные камни

### 1. Разыменование пустого `optional` — UB

```cpp
std::optional<int> value;
// int x = *value; // UB
```

Если состояние заранее не проверено, используйте `value()`.

### 2. `value_or` возвращает значение, а не ссылку

Для тяжёлого `T` это может привести к копированию. Кроме того, аргумент `value_or(...)` вычисляется до вызова метода, даже если значение внутри есть.

### 3. `optional` не хранит причину ошибки

Если вызывающему коду нужен код или текст ошибки, одного `optional` недостаточно. Используйте тип результата с ошибкой, например `std::expected` в C++23.

### 4. `std::optional<T&>` запрещён

Для необязательной невладеющей ссылки можно использовать указатель или `std::optional<std::reference_wrapper<T>>`.

### 5. Есть накладные расходы по памяти

Кроме `T`, нужен флаг и возможное выравнивание. `sizeof(optional<T>)` обычно больше `sizeof(T)`.

### 6. Copy elision зависит от возвращаемого выражения

При `return T{...};` из функции, возвращающей `optional<T>`, типы различаются и требуется конструирование значения внутри `optional`. При возврате самого `optional<T>` возможны обычные RVO/NRVO.

## Саммари

- `std::optional<T>` явно выражает возможное отсутствие значения.
- Пустое состояние обозначается `std::nullopt`.
- Наличие значения проверяется через `has_value()` или `operator bool`.
- `value()` проверяет состояние, а `*` и `->` требуют предварительной проверки.
- `value_or()` возвращает значение по умолчанию, но всегда по значению.
- `emplace` и `std::in_place` создают `T` непосредственно внутри `optional`.
- Для подробной информации об ошибке нужен более выразительный тип результата.
