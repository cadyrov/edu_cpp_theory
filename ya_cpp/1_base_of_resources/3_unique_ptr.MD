# 3. Эксклюзивное владение std::unique_ptr

## Суть

`std::unique_ptr` - умный указатель для эксклюзивного владения объектом.

Эксклюзивное владение означает: у объекта есть ровно один владелец.

Когда `unique_ptr` уничтожается, он сам вызывает `delete`.

```cpp
#include <memory>

int main() {
    std::unique_ptr<int> p = std::make_unique<int>(42);
}
```

`delete` писать не нужно.

## Зачем нужен

`unique_ptr` решает главную проблему `new/delete`: освобождение ресурса привязано к времени жизни объекта.

```cpp
#include <memory>

void may_throw();

void foo() {
    auto p = std::make_unique<int>(42);

    may_throw();
}
```

Если `may_throw()` бросит исключение, память все равно освободится.

## Пример 1: базовое владение

```cpp
#include <iostream>
#include <memory>

int main() {
    auto p = std::make_unique<int>(42);

    std::cout << *p << '\n';
}
```

Вывод:

```text
42
```

Разбор:

```cpp
auto p = std::make_unique<int>(42);
```

Создали `int` в динамической памяти. Владельцем стал `p`.

```cpp
std::cout << *p << '\n';
```

Получили значение как у обычного указателя.

В конце `main` объект `p` уничтожается и сам освобождает память.

## Пример 2: копировать нельзя

```cpp
#include <memory>

int main() {
    auto p1 = std::make_unique<int>(42);
    auto p2 = p1; // ошибка компиляции
}
```

Почему ошибка: два `unique_ptr` не могут владеть одним объектом.

Иначе оба попытались бы вызвать `delete`.

## Пример 3: владение можно переместить

```cpp
#include <iostream>
#include <memory>

int main() {
    auto p1 = std::make_unique<int>(42);
    auto p2 = std::move(p1);

    std::cout << *p2 << '\n';

    if (p1 == nullptr) {
        std::cout << "empty\n";
    }
}
```

Вывод:

```text
42
empty
```

Разбор:

```cpp
auto p2 = std::move(p1);
```

Владение объектом перешло из `p1` в `p2`.

После перемещения `p1` стал пустым.

## Пример 4: передача в функцию

```cpp
#include <memory>

void consume(std::unique_ptr<int> p) {
}

int main() {
    auto p = std::make_unique<int>(42);

    consume(std::move(p));
}
```

Функция `consume` забирает владение.

После вызова `p` в `main` больше не владеет объектом.

## Пример 5: get

```cpp
#include <iostream>
#include <memory>

void print(const int* p) {
    std::cout << *p << '\n';
}

int main() {
    auto p = std::make_unique<int>(42);

    print(p.get());
}
```

`get()` возвращает сырой указатель, но не передает владение.

Удалять результат `get()` нельзя:

```cpp
delete p.get(); // ошибка владения
```

## Пример 6: reset

```cpp
#include <memory>

int main() {
    auto p = std::make_unique<int>(42);

    p.reset();
}
```

`reset()` уничтожает текущий объект и делает `unique_ptr` пустым.

Можно заменить объект:

```cpp
p.reset(new int(100));
```

Но обычно лучше создавать через `std::make_unique`.

## Пример 7: release

```cpp
#include <memory>

int main() {
    auto p = std::make_unique<int>(42);

    int* raw = p.release();

    delete raw;
}
```

`release()` отдает сырой указатель и снимает владение с `unique_ptr`.

После `release()` удалять объект нужно вручную.

Использовать редко.

## Пример 8: массив

```cpp
#include <memory>

int main() {
    auto arr = std::make_unique<int[]>(3);

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
}
```

Для массива используется `std::unique_ptr<T[]>`.

Он вызывает `delete[]`, а не `delete`.

## Пример 9: кастомный удалитель

По умолчанию `std::unique_ptr<T>` освобождает объект через `delete`.

Иногда ресурс нужно освобождать другой функцией:

- `FILE*` через `std::fclose`;
- память из C API через специальную функцию библиотеки;
- дескриптор ОС через `close`/`CloseHandle`;
- объект из пула через возврат в пул.

Для этого у `unique_ptr` есть второй шаблонный параметр - deleter.

```cpp
#include <cstdio>
#include <memory>

struct FileDeleter {
    void operator()(FILE* file) const noexcept {
        if (file != nullptr) {
            std::fclose(file);
        }
    }
};

int main() {
    std::unique_ptr<FILE, FileDeleter> file(
        std::fopen("data.txt", "r")
    );

    if (file == nullptr) {
        return 1;
    }

    // используем file.get()
}
```

Когда `file` выйдет из области видимости, будет вызван `FileDeleter`.

### Лямбда как deleter

```cpp
#include <cstdio>
#include <memory>

int main() {
    auto deleter = [](FILE* file) noexcept {
        if (file != nullptr) {
            std::fclose(file);
        }
    };

    std::unique_ptr<FILE, decltype(deleter)> file(
        std::fopen("data.txt", "r"),
        deleter
    );
}
```

Важно: тип deleter-а входит в тип `unique_ptr`.

```cpp
std::unique_ptr<FILE> a;                    // удаляет через delete
std::unique_ptr<FILE, FileDeleter> b;       // удаляет через FileDeleter
```

Это разные типы.

### Почему не make_unique

`std::make_unique<T>()` создает `std::unique_ptr<T>` со стандартным удалителем.

Если нужен кастомный deleter, `make_unique` не подходит:

```cpp
auto file = std::make_unique<FILE>(); // плохо: FILE нельзя создавать так
```

Для таких случаев `unique_ptr` создают явно:

```cpp
std::unique_ptr<FILE, FileDeleter> file(
    std::fopen("data.txt", "r"),
    FileDeleter{}
);
```

Для обычных C++-объектов без особого способа освобождения лучше использовать `std::make_unique`.

### Кастомный удалитель и release

```cpp
auto raw = file.release();
```

После `release()` кастомный удалитель уже не будет вызван.

Ответственность за освобождение снова переходит к сырому указателю:

```cpp
if (raw != nullptr) {
    std::fclose(raw);
}
```

## Что будет выведено

```cpp
#include <iostream>
#include <memory>

int main() {
    auto p1 = std::make_unique<int>(10);
    auto p2 = std::move(p1);

    std::cout << *p2 << '\n';
    std::cout << (p1 == nullptr) << '\n';
}
```

Вывод:

```text
10
1
```

## Саммари

- `std::unique_ptr` владеет объектом единолично.
- Копировать `unique_ptr` нельзя.
- Передавать владение можно через `std::move`.
- `std::make_unique<T>()` лучше прямого `new`.
- `std::make_unique<T>()` создает `unique_ptr` со стандартным удалителем.
- `get()` дает сырой указатель без передачи владения.
- `reset()` удаляет текущий объект.
- `release()` отдает сырой указатель и снимает владение.
- Для массивов используется `std::unique_ptr<T[]>`.
- Для нестандартного освобождения ресурса используется кастомный deleter.
- Тип deleter-а является частью типа `std::unique_ptr`.
- Главная польза: `delete` вызывается автоматически.
