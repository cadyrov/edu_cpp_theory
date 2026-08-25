# 5. Монадические операции `std::optional`

## Суть

Цепочка функций, возвращающих `std::optional`, быстро обрастает одинаковыми проверками:

```cpp
auto user = FindUser(name);
if (!user) return std::nullopt;

auto profile = LoadProfile(user->id);
if (!profile) return std::nullopt;
```

В C++23 у `std::optional` появились монадические методы. Они автоматически прекращают цепочку при `std::nullopt`:

- `transform` — преобразует существующее значение;
- `and_then` — вызывает следующую функцию, уже возвращающую `optional`;
- `or_else` — обрабатывает отсутствие значения.

## Сравнение операций

| Метод | Когда вызывает функцию | Аргумент функции | Что должна вернуть функция | Результат |
|---|---|---|---|---|
| `transform` | Значение есть | Содержащийся `T` | Обычное значение `U` | `optional<U>` |
| `and_then` | Значение есть | Содержащийся `T` | `optional<U>` | `optional<U>` |
| `or_else` | Значения нет | Нет аргументов | `optional<T>` | `optional<T>` |

Если условие вызова не выполнено, функция не запускается.

## `transform`

`transform` применяет обычную функцию и сам оборачивает результат в новый `optional`.

```cpp
std::optional<int> number = 42;

auto text = number
    .transform([](int value) { return value * 2; })
    .transform([](int value) { return std::to_string(value); });

// optional<string>{"84"}
```

Для пустого значения цепочка остаётся пустой:

```cpp
std::optional<int> empty;
auto result = empty.transform(ToString); // nullopt
```

## `and_then`

`and_then` нужен, когда следующая функция сама может вернуть отсутствие значения.

```cpp
std::optional<int> GetUserAge(std::string_view name) {
    return FindUser(name)
        .and_then([](const User& user) {
            return LoadProfile(user.id);
        })
        .and_then([](const Profile& profile) {
            return ParseYear(profile.birthDate);
        })
        .transform(CalculateAge);
}
```

Здесь `FindUser`, `LoadProfile` и `ParseYear` возвращают `optional`, а `CalculateAge` — обычный `int`, поэтому в конце используется `transform`.

## `or_else`

`or_else` вызывается только для пустого `optional`. Его функция не получает аргументов и должна вернуть `optional<T>` того же типа.

```cpp
auto profile = LoadFromCache(id)
    .or_else([id] {
        return LoadFromDatabase(id);
    })
    .or_else([id] {
        ReportMissingProfile(id);
        return std::optional<Profile>{};
    });
```

Подход подходит для запасного источника, логирования и восстановления значения.

## Практическая цепочка

```cpp
HttpResponse ProcessRequest(std::string_view raw) {
    return ParseRequest(raw)
        .and_then(ValidateMethod)
        .and_then(ValidateVersion)
        .and_then(CheckHeaders)
        .transform(RouteRequest)
        .value_or(HttpResponse{400, "Bad Request"});
}
```

Пока функции проверки возвращают `optional<HttpRequest>`, используется `and_then`. Маршрутизация всегда создаёт ответ, поэтому применяется `transform`.

## Значения и категории ссылок

У монадических методов есть перегрузки для `&`, `const&`, `&&` и `const&&`. Это позволяет не копировать тяжёлые значения:

```cpp
auto result = std::move(optionalValue)
    .transform([](LargeObject value) {
        return Process(std::move(value));
    });
```

Без `std::move` содержащийся объект передаётся как lvalue. Выбирайте параметр лямбды (`T`, `T&`, `const T&`) осознанно.

## `optional` как диапазон в C++26

В C++26 `std::optional<T>` получает `begin()` и `end()` и становится диапазоном из нуля или одного элемента.

До C++26 извлечение значений из диапазона `optional` выглядит так:

```cpp
auto names = letters
    | std::views::transform(&Letter::GetSenderName)
    | std::views::filter(&std::optional<std::string>::has_value)
    | std::views::transform([](const auto& value) {
          return *value;
      });
```

В C++26 внутренние диапазоны можно объединить:

```cpp
auto names = letters
    | std::views::transform(&Letter::GetSenderName)
    | std::views::join;
```

Поддержка этой возможности конкретным компилятором и стандартной библиотекой может появиться не сразу.

## Пользовательские операторы

Цепочки можно стилизовать под функциональные языки собственными `operator|` или `operator>>=`. Однако обычные методы понятнее большинству C++-разработчиков и не создают проблем с приоритетами операторов и разрешением перегрузок.

```cpp
template <typename T, typename F>
auto operator|(std::optional<T>&& value, F&& function) {
    return std::move(value).transform(std::forward<F>(function));
}
```

Такой оператор поддерживает только выбранный контракт и не является частью стандартного интерфейса `optional`.

## Подводные камни

### 1. Не путайте `transform` и `and_then`

Если функция возвращает `optional<U>`, вызов `transform` создаст вложенный `optional<optional<U>>`. Для такой функции нужен `and_then`.

### 2. `or_else` не получает ошибку

`optional` хранит только факт отсутствия значения. Если нужна причина сбоя, используйте `std::expected<T, E>` или другой тип результата.

### 3. `value_or` вычисляет запасное значение заранее

```cpp
auto value = opt.value_or(ExpensiveFallback());
```

`ExpensiveFallback()` вызывается до `value_or`, даже если `opt` непуст. Для ленивого восстановления используйте `or_else`.

### 4. Следите за временем жизни ссылок

Не возвращайте из `transform` ссылки или представления на уничтожаемые временные объекты.

### 5. Монадический интерфейс требует C++23

В C++17/20 методы `transform`, `and_then` и `or_else` отсутствуют в стандартном `optional`.

### 6. `optional` как range требует C++26

Код с `views::join` над `optional` не обязан компилироваться в C++23.

## Саммари

- Монадические методы убирают повторяющиеся проверки `if (!opt)`.
- `transform`: `T -> U`.
- `and_then`: `T -> optional<U>`.
- `or_else`: `nullopt -> optional<T>`.
- Пустое значение автоматически прерывает успешную ветку цепочки.
- `optional` не хранит сведения о причине ошибки.
- В C++26 `optional` становится диапазоном из нуля или одного элемента.
