# 5. Передача владения: move-семантика и обмен состояниями

## Суть

Move-семантика нужна, чтобы не копировать ресурс, а передать владение им.

Копирование:

```cpp
std::string b = a;
```

Перемещение:

```cpp
std::string b = std::move(a);
```

`std::move` сам ничего не перемещает. Он только разрешает использовать объект как временный.

Реальное перемещение делает move constructor или move assignment.

## Зачем нужно

Для ресурсов копирование часто:

- дорогое;
- запрещено;
- опасно.

Например, `std::unique_ptr` нельзя копировать, но можно перемещать.

```cpp
auto p1 = std::make_unique<int>(42);
auto p2 = std::move(p1);
```

Владение перешло из `p1` в `p2`.

## Пример 1: move с unique_ptr

```cpp
#include <iostream>
#include <memory>

int main() {
    auto p1 = std::make_unique<int>(42);
    auto p2 = std::move(p1);

    std::cout << *p2 << '\n';
    std::cout << (p1 == nullptr) << '\n';
}
```

Вывод:

```text
42
1
```

Разбор:

```cpp
auto p2 = std::move(p1);
```

`p2` забрал владение.

`p1` стал пустым.

## Пример 2: передача владения в функцию

```cpp
#include <memory>

void consume(std::unique_ptr<int> p) {
}

int main() {
    auto p = std::make_unique<int>(42);

    consume(std::move(p));
}
```

Разбор:

```cpp
consume(std::move(p));
```

Функция забрала владение.

После вызова `p == nullptr`.

## Пример 3: возврат владения из функции

```cpp
#include <memory>

std::unique_ptr<int> create() {
    return std::make_unique<int>(42);
}

int main() {
    auto p = create();
}
```

Функция возвращает `unique_ptr`.

Владение переходит наружу.

## Пример 4: свой класс с ресурсом

```cpp
#include <utility>

class Buffer {
public:
    explicit Buffer(int size)
        : size_(size), data_(new int[size]) {
    }

    ~Buffer() {
        delete[] data_;
    }

    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    Buffer(Buffer&& other) noexcept
        : size_(other.size_), data_(other.data_) {
        other.size_ = 0;
        other.data_ = nullptr;
    }

    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data_;

            size_ = other.size_;
            data_ = other.data_;

            other.size_ = 0;
            other.data_ = nullptr;
        }

        return *this;
    }

private:
    int size_ = 0;
    int* data_ = nullptr;
};
```

Разбор:

```cpp
Buffer(const Buffer&) = delete;
```

Копирование запрещено.

```cpp
Buffer(Buffer&& other) noexcept
```

Move constructor забирает ресурс у другого объекта.

```cpp
other.data_ = nullptr;
```

Старый объект оставляют в безопасном пустом состоянии.

## Пример 5: moved-from state

После перемещения объект должен быть валидным, но его значение обычно не важно.

```cpp
auto p1 = std::make_unique<int>(42);
auto p2 = std::move(p1);

if (p1 == nullptr) {
    // нормально
}
```

Для `std::unique_ptr` состояние после move четкое: он становится `nullptr`.

Для других типов гарантируется только: объект можно уничтожить или присвоить ему новое значение.

## Пример 6: обмен состояниями

```cpp
#include <iostream>
#include <memory>
#include <utility>

int main() {
    auto a = std::make_unique<int>(10);
    auto b = std::make_unique<int>(20);

    std::swap(a, b);

    std::cout << *a << '\n';
    std::cout << *b << '\n';
}
```

Вывод:

```text
20
10
```

`swap` обменивает состояния объектов.

Для владеющих типов это часто дешевле и безопаснее копирования.

## Пример 7: move assignment

```cpp
#include <iostream>
#include <memory>

int main() {
    auto a = std::make_unique<int>(10);
    auto b = std::make_unique<int>(20);

    a = std::move(b);

    std::cout << *a << '\n';
    std::cout << (b == nullptr) << '\n';
}
```

Вывод:

```text
20
1
```

Разбор:

```cpp
a = std::move(b);
```

Старый объект внутри `a` удален.

Владение объектом из `b` перешло в `a`.

`b` стал пустым.

## Частые ошибки

### Использовать объект после move как будто он прежний

```cpp
auto p1 = std::make_unique<int>(42);
auto p2 = std::move(p1);

std::cout << *p1; // ошибка: p1 == nullptr
```

### Думать, что std::move перемещает сам

```cpp
std::move(x);
```

Эта строка сама по себе ничего полезного не делает.

## Саммари

- Move-семантика передает владение ресурсом.
- `std::move` не перемещает сам, а разрешает перемещение.
- Реальное перемещение делает move constructor или move assignment.
- `std::unique_ptr` нельзя копировать, но можно перемещать.
- После move объект должен быть валидным.
- Для `std::unique_ptr` после move обычно `nullptr`.
- `swap` обменивает состояния объектов.
- Move constructor создает новый объект из старого.
- Move assignment заменяет ресурс уже существующего объекта.
