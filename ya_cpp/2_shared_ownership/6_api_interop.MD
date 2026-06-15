# 6. Взаимодействие с API-библиотекой

## Суть

При работе с внешним API важно понимать контракт владения.

Главный вопрос: кто должен освободить ресурс?

Умные указатели помогают выразить этот контракт в коде.

```cpp
void use(const int* p);
void consume(std::unique_ptr<int> p);
```

Первая функция только использует объект.

Вторая забирает владение.

## Пример 1: передача без владения через get

```cpp
#include <iostream>
#include <memory>
#include <utility>

void print(const int* p) {
    std::cout << *p << '\n';
}

int main() {
    auto value = std::make_unique<int>(42);

    print(value.get());
}
```

Вывод:

```text
42
```

`get()` возвращает сырой указатель.

Владение остается у `unique_ptr`.

Удалять результат `get()` нельзя.

## Пример 2: передача владения

```cpp
#include <memory>

void consume(std::unique_ptr<int> p) {
}

int main() {
    auto value = std::make_unique<int>(42);

    consume(std::move(value));
}
```

Функция `consume` забирает владение.

После вызова `value` стал пустым.

## Пример 3: API возвращает сырой указатель

```cpp
#include <memory>

int* create_value() {
    return new int(42);
}

int main() {
    std::unique_ptr<int> value(create_value());
}
```

Если API отдает владение через сырой указатель, его можно сразу положить в `unique_ptr`.

Так `delete` будет вызван автоматически.

## Пример 4: custom deleter

```cpp
#include <cstdio>
#include <memory>

int main() {
    std::unique_ptr<FILE, decltype(&std::fclose)> file(
        std::fopen("data.txt", "r"),
        &std::fclose
    );
}
```

`FILE*` нужно закрывать через `fclose`, а не через `delete`.

Для этого используется custom deleter.

## Пример 5: shared_ptr с custom deleter

```cpp
#include <cstdio>
#include <memory>

int main() {
    std::shared_ptr<FILE> file(
        std::fopen("data.txt", "r"),
        [](FILE* f) {
            if (f) {
                std::fclose(f);
            }
        }
    );
}
```

Когда исчезнет последний `shared_ptr`, будет вызван deleter.

Это удобно, если ресурс действительно нужен нескольким владельцам.

## Пример 6: callback и время жизни

```cpp
#include <functional>
#include <memory>

struct Worker {
    void run() {
    }
};

std::function<void()> make_callback(std::shared_ptr<Worker> worker) {
    return [worker] {
        worker->run();
    };
}
```

Лямбда хранит `shared_ptr`.

`Worker` будет жить, пока жив callback.

Если продлевать жизнь объекта не нужно, можно хранить `weak_ptr`.

```cpp
std::function<void()> make_callback(std::weak_ptr<Worker> worker) {
    return [worker] {
        if (auto locked = worker.lock()) {
            locked->run();
        }
    };
}
```

## Подводные камни

### get не передает владение

Плохо:

```cpp
auto value = std::make_unique<int>(42);

delete value.get();
```

`unique_ptr` потом тоже попытается удалить объект.

### release требует ручного освобождения

```cpp
auto value = std::make_unique<int>(42);
int* raw = value.release();
```

После `release()` `unique_ptr` больше не владеет объектом.

Теперь кто-то обязан вызвать `delete raw`.

Использовать редко.

### Нельзя хранить сырой указатель дольше владельца

Плохо:

```cpp
int* raw = nullptr;

{
    auto value = std::make_unique<int>(42);
    raw = value.get();
}

// raw теперь висячий
```

Сырой указатель не продлевает жизнь объекта.

### Нужен правильный способ освобождения

Не все ресурсы освобождаются через `delete`.

Примеры:

- `FILE*` закрывается через `fclose`;
- C-объект может требовать `destroy_x`;
- память из C API может требовать специальную функцию освобождения.

Для этого нужен custom deleter.

## Что будет выведено

```cpp
#include <iostream>
#include <memory>
#include <utility>

void print(const int* p) {
    std::cout << *p << '\n';
}

int main() {
    auto value = std::make_unique<int>(42);

    print(value.get());

    auto moved = std::move(value);

    std::cout << (value == nullptr) << '\n';
}
```

Вывод:

```text
42
1
```

## Саммари

- В API важно явно понимать контракт владения.
- `get()` дает доступ, но не передает владение.
- Удалять результат `get()` нельзя.
- `unique_ptr` в параметре обычно означает передачу владения.
- `release()` снимает владение и требует ручного освобождения.
- Для C API часто нужен custom deleter.
- Сырой указатель не продлевает жизнь объекта.
- Callback с `shared_ptr` продлевает жизнь объекта.
- Callback с `weak_ptr` проверяет, жив ли объект.
