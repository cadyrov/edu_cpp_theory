# 4. Case study: динамически обновляемая конфигурация

## Суть

Конфигурацию часто читают много потоков.

Обновляется она редко.

Удобный подход: хранить конфигурацию как immutable-объект и заменять целиком через `std::shared_ptr`.

Читатель берет свою копию `shared_ptr` и спокойно работает с выбранной версией.

## Пример 1: конфигурация как объект

```cpp
#include <string>

struct Config {
    std::string host;
    int port = 0;
};
```

После публикации такую конфигурацию лучше не менять.

Если настройки изменились, создается новый `Config`.

## Пример 2: хранение текущей версии

```cpp
#include <atomic>
#include <memory>
#include <string>

struct Config {
    std::string host;
    int port = 0;
};

class ConfigStorage {
public:
    void update(std::shared_ptr<const Config> config) {
        current_.store(std::move(config));
    }

    std::shared_ptr<const Config> get() const {
        return current_.load();
    }

private:
    std::atomic<std::shared_ptr<const Config>> current_;
};
```

`std::shared_ptr<const Config>` означает: читатели не должны менять конфигурацию.

`atomic` позволяет заменить текущую версию целиком.

## Пример 3: чтение конфигурации

```cpp
#include <iostream>

void handle_request(const ConfigStorage& storage) {
    auto config = storage.get();

    if (!config) {
        return;
    }

    std::cout << config->host << ':' << config->port << '\n';
}
```

`config` - локальная копия `shared_ptr`.

Пока она живет, версия конфигурации не будет уничтожена.

## Пример 4: обновление конфигурации

```cpp
auto config = std::make_shared<Config>();
config->host = "localhost";
config->port = 8080;

storage.update(config);
```

После `update` новые читатели увидят новую версию.

Старые читатели могут еще держать старую версию.

Это нормально.

## Пример 5: старая версия живет у читателя

```cpp
#include <atomic>
#include <iostream>
#include <memory>

int main() {
    std::atomic<std::shared_ptr<const int>> current;

    current.store(std::make_shared<int>(10));

    auto reader_version = current.load();

    current.store(std::make_shared<int>(20));

    std::cout << *reader_version << '\n';
    std::cout << *current.load() << '\n';
}
```

Вывод:

```text
10
20
```

Читатель продолжает работать со старой версией.

Новая версия уже опубликована для следующих читателей.

## Подводные камни

### Не меняйте опубликованную конфигурацию

Плохо:

```cpp
auto config = storage.get();
config->port = 9000; // если Config не const
```

Так разные читатели могут увидеть неожиданные изменения.

Лучше публиковать `std::shared_ptr<const Config>`.

### Не возвращайте сырую ссылку на текущую конфигурацию

Плохо:

```cpp
const Config& get();
```

Если хранилище заменит конфигурацию, ссылка может стать опасной.

Лучше вернуть `std::shared_ptr<const Config>`.

### Не смешивайте частичное обновление и атомарную публикацию

Плохо:

```cpp
auto config = storage.get();
// меняем поля по одному
```

Читатель может увидеть промежуточное состояние.

Правильно: собрать новый объект полностью и только потом опубликовать.

## Что будет выведено

```cpp
#include <atomic>
#include <iostream>
#include <memory>

int main() {
    std::atomic<std::shared_ptr<const int>> current;

    current.store(std::make_shared<int>(1));

    auto first = current.load();

    current.store(std::make_shared<int>(2));

    auto second = current.load();

    std::cout << *first << '\n';
    std::cout << *second << '\n';
}
```

Вывод:

```text
1
2
```

## Саммари

- Конфигурацию удобно хранить как immutable-объект.
- Текущую версию можно хранить в `std::atomic<std::shared_ptr<const Config>>`.
- Читатель берет локальную копию `shared_ptr`.
- Пока копия живет, версия конфигурации не удаляется.
- Обновление делается созданием нового объекта и атомарной публикацией.
- Старые читатели могут спокойно дочитать старую версию.
- Не меняйте уже опубликованную конфигурацию.
