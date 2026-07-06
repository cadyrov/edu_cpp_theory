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

## Пример 6: C API с out-параметром

Некоторые C API возвращают ресурс не через `return`, а через указатель на указатель.

```cpp
struct Handle;

int create_handle(Handle** out);
void destroy_handle(Handle* handle);
```

До C++23 такой код часто писали вручную:

```cpp
#include <memory>
#include <stdexcept>

struct HandleDeleter {
    void operator()(Handle* handle) const noexcept {
        if (handle != nullptr) {
            destroy_handle(handle);
        }
    }
};

using HandlePtr = std::unique_ptr<Handle, HandleDeleter>;

HandlePtr make_handle() {
    Handle* raw = nullptr;

    if (create_handle(&raw) != 0) {
        throw std::runtime_error("create_handle failed");
    }

    return HandlePtr(raw);
}
```

Проблема: между получением `raw` и помещением в `unique_ptr` легко ошибиться.

## Пример 7: std::out_ptr

`std::out_ptr` адаптирует умный указатель под C API, которое записывает новый ресурс в `T**`.

```cpp
#include <memory>

HandlePtr make_handle() {
    HandlePtr handle;

    if (create_handle(std::out_ptr(handle)) != 0) {
        throw std::runtime_error("create_handle failed");
    }

    return handle;
}
```

Идея:

- C API получает `Handle**`;
- после вызова новый сырой указатель автоматически попадает в `handle`;
- освобождение остается за `unique_ptr` и его deleter-ом.

`std::out_ptr` нужен, когда C API создает новый ресурс.

## Пример 8: std::inout_ptr

`std::inout_ptr` нужен, когда C API принимает старый ресурс и может заменить его новым.

```cpp
int reload_handle(Handle** inout);

void reload(HandlePtr& handle) {
    if (reload_handle(std::inout_ptr(handle)) != 0) {
        throw std::runtime_error("reload_handle failed");
    }
}
```

Идея:

- текущий ресурс передается в C API;
- C API может заменить указатель;
- после вызова `unique_ptr` снова владеет актуальным ресурсом.

`std::inout_ptr` используют осторожно: нужно понимать контракт C API.

Если API сначала освобождает старый ресурс, а потом пишет новый, это один контракт.

Если API ожидает, что старый ресурс освободит вызывающая сторона, это другой контракт.

Для ошибки тоже важен контракт: изменился ли out-параметр при неуспешном возврате.

## Пример 9: callback и время жизни

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

### out_ptr и inout_ptr

`std::out_ptr` и `std::inout_ptr` появились в C++23.

Они нужны для аккуратной передачи `unique_ptr`/`shared_ptr` в C API с параметрами вида `T**`.

```cpp
create_handle(std::out_ptr(handle));   // API создает новый ресурс
reload_handle(std::inout_ptr(handle)); // API может заменить существующий ресурс
```

Не используй `&ptr.get()`: `get()` возвращает значение указателя, а не место, куда можно записать новый указатель.

Если C++23 недоступен, обычно используют временный сырой указатель и сразу оборачивают его в умный указатель.

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
- `std::out_ptr` адаптирует умный указатель для C API, которое создает ресурс через `T**`.
- `std::inout_ptr` адаптирует умный указатель для C API, которое может заменить уже существующий ресурс.
- Сырой указатель не продлевает жизнь объекта.
- Callback с `shared_ptr` продлевает жизнь объекта.
- Callback с `weak_ptr` проверяет, жив ли объект.
