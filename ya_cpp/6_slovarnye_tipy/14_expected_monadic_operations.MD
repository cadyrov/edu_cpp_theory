# 14. Монадические операции `std::expected`

## Суть

Последовательность функций, возвращающих `expected`, можно объединить без повторяющихся проверок:

```cpp
auto response = ParseRequest(raw)
    .and_then(ValidateMethod)
    .and_then(ValidateVersion)
    .transform(RouteRequest)
    .transform_error(ToResponseError);
```

При первой ошибке успешная ветка прекращается, а ошибка передаётся дальше до обработчика.

Монадический интерфейс `std::expected` появился вместе с ним в C++23.

## Основные операции

Для `std::expected<T, E>`:

| Метод | Когда вызывается | Функция | Результат | Может изменить |
|---|---|---|---|---|
| `and_then` | Есть значение | `T -> expected<U, E>` | `expected<U, E>` | Тип значения |
| `transform` | Есть значение | `T -> U` | `expected<U, E>` | Тип значения |
| `or_else` | Есть ошибка | `E -> expected<T, G>` | `expected<T, G>` | Тип ошибки |
| `transform_error` | Есть ошибка | `E -> G` | `expected<T, G>` | Тип ошибки |

Неактивная ветка не вызывается.

## `and_then`

`and_then` соединяет функции, каждая из которых может завершиться ошибкой.

```cpp
std::expected<HttpRequest, RequestError>
ParseRequest(std::string_view raw);

std::expected<HttpRequest, RequestError>
ValidateMethod(HttpRequest request);

std::expected<HttpRequest, RequestError>
ValidateVersion(HttpRequest request);

auto result = ParseRequest(raw)
    .and_then(ValidateMethod)
    .and_then(ValidateVersion);
```

Если `ParseRequest` вернул ошибку, функции в следующих `and_then` не вызываются.

Тип успешного значения может измениться:

```cpp
std::expected<UserId, Error> FindUser(std::string_view name);
std::expected<User, Error> LoadUser(UserId id);

std::expected<User, Error> user =
    FindUser("Alice").and_then(LoadUser);
```

Ошибка должна оставаться совместимой с типом `E` цепочки.

## `transform`

`transform` применяет функцию, которая возвращает обычное значение, и сам оборачивает результат.

```cpp
std::expected<HttpResponse, RequestError> response =
    ParseRequest(raw)
        .and_then(ValidateMethod)
        .transform(RouteRequest);
```

```text
HttpRequest -> HttpResponse
expected<HttpRequest, Error> -> expected<HttpResponse, Error>
```

Если callback возвращает `void`, результатом становится `expected<void, E>`.

## `transform_error`

`transform_error` преобразует ошибку между слоями приложения:

```cpp
enum class LibraryError {
    ReadFailed,
    Unsupported
};

struct AppError {
    std::string message;
};

AppError ToAppError(LibraryError error) {
    return AppError{Describe(error)};
}

std::expected<Data, AppError> result =
    ReadFromLibrary().transform_error(ToAppError);
```

Успешное значение передаётся без изменения:

```text
expected<T, LibraryError> -> expected<T, AppError>
```

Этот метод полезен на границах библиотек и архитектурных слоёв.

## `or_else`

`or_else` вызывается только при ошибке и получает её аргументом:

```cpp
auto result = LoadFromCache(id)
    .or_else([id](CacheError error) {
        Log(error);
        return LoadFromDatabase(id);
    });
```

Callback возвращает новый `expected` с тем же типом значения. Он может:

- восстановить успешное значение;
- заменить ошибку;
- залогировать и передать ошибку дальше.

```cpp
auto result = Load(id).or_else([](LoadError error) {
    Log(error);
    return std::expected<Data, LoadError>{
        std::unexpected{error}
    };
});
```

## Полная обработка HTTP-запроса

```cpp
using Result = std::expected<HttpResponse, ResponseError>;

Result ProcessRequest(std::string_view raw) {
    return ParseRequest(raw)
        .and_then(ValidateMethod)
        .and_then(ValidateVersion)
        .and_then(CheckHeaders)
        .transform(RouteRequest)
        .transform_error(ToResponseError)
        .or_else([](ResponseError error) -> Result {
            if (IsSuspicious(error)) {
                ReportSecurityIncident(error);
            }
            return std::unexpected{std::move(error)};
        });
}
```

Успешная ветка и преобразование ошибок читаются линейно.

## Сравнение с `std::optional`

| Операция | `std::optional<T>` | `std::expected<T, E>` |
|---|---|---|
| `and_then` | Пустота передаётся дальше | Ошибка `E` передаётся дальше |
| `transform` | Меняет тип значения | Меняет тип значения |
| `or_else` | Callback без аргументов | Callback получает ошибку `E` |
| `transform_error` | Нет | Преобразует `E` в `G` |
| Причина неуспеха | Не хранится | Доступна через `error()` |

Наблюдатели `operator bool`, `has_value`, `*`, `->`, `value` и `value_or` имеют похожую семантику.

`error_or` и `has_error` присутствуют в актуальном интерфейсе C++26; для переносимого C++23 используйте проверку `!result` и `error()`.

## Категории значений

У методов есть перегрузки для `&`, `const&`, `&&` и `const&&`. Категория объекта определяет, копируется или перемещается значение/ошибка.

```cpp
auto result = std::move(source)
    .and_then([](LargeValue value) {
        return Process(std::move(value));
    });
```

Без `std::move(source)` callback обычно получает lvalue-ссылку. Для тяжёлых и move-only типов выбирайте параметры и категорию цепочки осознанно.

## Восстановление до обычного значения

Если `or_else` гарантированно превращает любую ошибку в успех, после него можно безопасно извлечь значение:

```cpp
std::string message = TryLogin(name, password)
    .transform([](const User& user) {
        return "Welcome, " + user.displayName;
    })
    .or_else([](LoginError error) {
        return std::expected<std::string, LoginError>{
            "Login failed: " + Describe(error)
        };
    })
    .value();
```

Часто проще вернуть сам `expected` наружу, сохранив возможность вызывающему коду выбрать политику ошибки.

## Подводные камни

### 1. Не путайте `transform` и `and_then`

```cpp
// Validate возвращает expected<U, E>.
source.transform(Validate); // expected<expected<U, E>, E>
source.and_then(Validate);  // expected<U, E>
```

### 2. Не путайте `transform_error` и `or_else`

`transform_error` возвращает обычную новую ошибку `G`. `or_else` возвращает целый `expected<T, G>` и может восстановить значение.

### 3. `or_else` у `optional` и `expected` различается

У `optional` callback не имеет аргументов. У `expected` он получает текущую ошибку.

### 4. Логирование должно сохранить результат

После побочного эффекта в `or_else` верните `unexpected` с ошибкой, иначе можно случайно превратить сбой в успех.

### 5. `value_or` вычисляет fallback заранее

Для дорогого ленивого восстановления используйте `or_else`.

### 6. Тип ошибки в `and_then` должен согласовываться

Если соседние функции используют разные ошибки, сначала приведите их к общему типу через `transform_error`.

### 7. Длинная цепочка не всегда читаемее

Давайте осмысленные имена функциям, не помещайте сложные побочные эффекты в большие лямбды и разделяйте архитектурные слои.

### 8. Сохраняйте контекст ошибки

При `transform_error` не заменяйте полезную низкоуровневую диагностику общим `Unknown`, если её можно вложить в ошибку верхнего уровня.

## Саммари

- `and_then`: успешная функция уже возвращает `expected`.
- `transform`: успешная функция возвращает обычное значение.
- `transform_error`: преобразует объект и тип ошибки.
- `or_else`: обрабатывает ошибку и возвращает новый `expected`.
- Ошибка автоматически прерывает успешную часть цепочки.
- Разные типы ошибок сводятся к общему через `transform_error`.
- `or_else` подходит для восстановления, логирования и запасного пути.
- Монадические методы доступны у `expected` с C++23.
