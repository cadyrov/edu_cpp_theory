# 1. Ручное управление памятью: от malloc/free к new/delete

В C++ можно создавать объекты в автоматической памяти:

```cpp
int x = 10;
```

А можно вручную выделять память в куче:

```cpp
int* p = new int(10);
```

Если память выделена через `new`, ее нужно вручную освободить через `delete`:

```cpp
delete p;
```

Главная идея темы: если ты сам запросил память, ты сам обязан ее вернуть.

## malloc/free

`malloc/free` пришли из C.

```cpp
int* p = (int*)malloc(sizeof(int));
*p = 10;

free(p);
```

`malloc` просто выделяет сырые байты. Он не создает C++-объект и не вызывает конструктор.

`free` просто освобождает память. Он не вызывает деструктор C++-объекта.

## new/delete

`new/delete` - C++-способ ручного управления памятью.

```cpp
int* p = new int(10);

delete p;
```

`new` делает две вещи:

1. выделяет память;
2. создает объект.

`delete` тоже делает две вещи:

1. уничтожает объект;
2. освобождает память.

## Пример 1

```cpp
#include <iostream>

int main() {
    int* p = new int(42);

    std::cout << *p << '\n';

    delete p;
}
```

Вывод:

```text
42
```

## Разбор

```cpp
int* p = new int(42);
```

Создается объект типа `int` в динамической памяти. В нем лежит значение `42`.

```cpp
std::cout << *p << '\n';
```

`p` хранит адрес. `*p` получает значение по этому адресу.

```cpp
delete p;
```

Объект уничтожается, память освобождается.

После `delete p` указатель `p` все еще хранит старый адрес, но использовать его уже нельзя.

```cpp
delete p;
std::cout << *p; // ошибка: undefined behavior
```

## Корректная обработка объекта

### 1. malloc/free

`malloc` при ошибке возвращает `nullptr`.

```cpp
#include <cstdlib>
#include <new>

struct User {
    User(int id) {}
    ~User() {}
};

int main() {
    void* memory = std::malloc(sizeof(User));
    if (memory == nullptr) {
        return 1;
    }

    User* user = new (memory) User(42);

    user->~User();
    std::free(memory);
}
```

Смысл:

- `malloc` выделяет память;
- placement new создает объект в этой памяти;
- явный вызов деструктора уничтожает объект;
- `free` освобождает память.

### 2. ::operator new / ::operator delete

`::operator new` при ошибке бросает `std::bad_alloc`.

```cpp
#include <new>

struct User {
    User(int id) {}
    ~User() {}
};

int main() {
    void* memory = ::operator new(sizeof(User));

    User* user = new (memory) User(42);

    user->~User();
    ::operator delete(memory);
}
```

Смысл:

- `::operator new` выделяет сырую память;
- placement new создает объект;
- деструктор вызывается вручную;
- `::operator delete` освобождает память.

### 3. new/delete

Обычный `new` при ошибке бросает `std::bad_alloc`.

```cpp
struct User {
    User(int id) {}
    ~User() {}
};

int main() {
    User* user = new User(42);

    delete user;
}
```

Смысл:

- `new` выделяет память и создает объект;
- `delete` вызывает деструктор и освобождает память.

## Размещающая форма new

Размещающая форма `new` = placement new.

```cpp
new (address) T(args...);
```

Она не выделяет память. Она только создает объект по готовому адресу.

```cpp
#include <cstdlib>
#include <new>

struct User {
    User(int id) {}
    ~User() {}
};

int main() {
    void* memory = std::malloc(sizeof(User));
    if (memory == nullptr) {
        return 1;
    }

    User* user = new (memory) User(42);

    user->~User();
    std::free(memory);
}
```

Правило: если объект создан через placement new, деструктор вызывается вручную.

```cpp
user->~User();
```

`delete user` здесь нельзя, потому что память была выделена не обычным `new`.

## Placement new и выравнивание

Память должна быть:

- достаточно большой;
- правильно выровненной.

Так лучше не делать:

```cpp
char buffer[sizeof(User)];
User* user = new (buffer) User(42); // может быть неправильное выравнивание
```

Корректнее:

```cpp
#include <cstddef>
#include <new>

struct User {
    User(int id) {}
    ~User() {}
};

int main() {
    alignas(User) std::byte buffer[sizeof(User)];

    User* user = new (buffer) User(42);

    user->~User();
}
```

`alignas(User)` говорит: выровнять буфер так, чтобы в нем можно было хранить `User`.

У `alignas` есть две частые формы:

```cpp
alignas(64) std::byte buffer[1024];     // выравнивание в байтах
alignas(User) std::byte raw[sizeof(User)]; // выравнивание как у типа User
```

Общая форма:

```cpp
alignas(размер_в_байтах) тип имя;
alignas(другой_тип) тип имя;
```

`std::byte` лучше показывает смысл такого буфера: это сырая память как набор байтов, а не строка или число.

В отличие от `unsigned char`, `std::byte` не является символьным или арифметическим типом. С ним нельзя случайно сделать обычную арифметику:

```cpp
std::byte b{42};
// b + 1; // ошибка
```

При этом побитовые операции разрешены:

```cpp
auto flags = std::byte{0b0011} | std::byte{0b0100};
```

Пример с ошибками выравнивания и aliasing:

```cpp
#include <cstdint>
#include <new>
#include <print>

struct AlignedStruct {
    std::int32_t a;
    std::int64_t b;
};

struct A {
    int x;
};

struct B {
    int x;
};

int main() {
    alignas(4) std::byte buffer[12];
    auto* ptr1 = reinterpret_cast<std::int64_t*>(&buffer[4]); // 1
    *ptr1 = 42;                                               // 2

    int intValue = 10;
    auto* ptr2 = reinterpret_cast<float*>(&intValue); // 3
    *ptr2 = 3.14f;                                    // 4

    alignas(4) std::byte rawMemory[32];
    auto* ptr3 = new (rawMemory) AlignedStruct{1, 2}; // 5

    std::print("Object Info: a: {}, b: {}\n", ptr3->a, ptr3->b); // 6

    static_assert(sizeof(AlignedStruct) ==
                  sizeof(std::int32_t) + sizeof(std::int64_t)); // 7

    alignas(alignof(AlignedStruct)) std::byte buf[sizeof(AlignedStruct)]; // 8
    auto* ptr6 = new (buf) AlignedStruct{3, 4};                           // 9
    std::print("Object Info: a: {}, b: {}\n", ptr6->a, ptr6->b);          // 10

    union {
        int intVal;
        float floatVal;
    } u;
    u.intVal = 42;      // 11
    u.floatVal = 24.f;  // 12

    A a{42};
    int xValue = reinterpret_cast<B*>(&a)->x; // 13
}
```

Проблемные строки:

- `1`, `2`: адрес `&buffer[4]` не обязан быть выровнен под `std::int64_t`.
- `3`, `4`: объект `int` нельзя использовать как `float`, это нарушение strict aliasing.
- `5`, `6`: `rawMemory` выровнен только на 4 байта, а `AlignedStruct` требует выравнивание как минимум под `std::int64_t`.
- `7`: `sizeof(AlignedStruct)` обычно больше суммы полей из-за padding.
- `13`: объект типа `A` нельзя читать как объект типа `B`, даже если поля совпадают.

Строки `8`, `9`, `10` корректно учитывают выравнивание через `alignof(AlignedStruct)`.

## Корректная обработка массива

### 1. malloc/free

```cpp
#include <cstdlib>
#include <new>

struct User {
    User() {}
    ~User() {}
};

int main() {
    const int n = 3;

    void* memory = std::malloc(sizeof(User) * n);
    if (memory == nullptr) {
        return 1;
    }

    User* users = static_cast<User*>(memory);

    for (int i = 0; i < n; ++i) {
        new (&users[i]) User();
    }

    for (int i = n - 1; i >= 0; --i) {
        users[i].~User();
    }

    std::free(memory);
}
```

### 2. ::operator new[] / ::operator delete[]

```cpp
#include <new>

struct User {
    User() {}
    ~User() {}
};

int main() {
    const int n = 3;

    void* memory = ::operator new[](sizeof(User) * n);
    User* users = static_cast<User*>(memory);

    for (int i = 0; i < n; ++i) {
        new (&users[i]) User();
    }

    for (int i = n - 1; i >= 0; --i) {
        users[i].~User();
    }

    ::operator delete[](memory);
}
```

### 3. new[]/delete[]

```cpp
struct User {
    User() {}
    ~User() {}
};

int main() {
    User* users = new User[3];

    delete[] users;
}
```

Смысл:

- `new[]` создает все элементы массива;
- `delete[]` уничтожает все элементы массива и освобождает память.

## Несовместимые пары

Правильные пары:

```cpp
std::malloc(...)       -> std::free(...)
::operator new(...)   -> ::operator delete(...)
new T(...)            -> delete
new T[n]              -> delete[]
```

Так нельзя:

```cpp
int* p = new int(42);
std::free(p); // undefined behavior
```

```cpp
int* p = (int*)std::malloc(sizeof(int));
delete p; // undefined behavior
```

```cpp
User* users = new User[3];
delete users; // undefined behavior, нужен delete[]
```

У `new[]` может быть служебная область перед массивом: array cookie/count.

Упрощенно:

```text
[count][User][User][User]
        ^
        users
```

`delete[]` знает, что нужно уничтожить все элементы массива.

`delete` думает, что перед ним один объект.

## Undefined behavior

Undefined behavior - ситуация, где C++ ничего не гарантирует.

Код может:

- работать;
- падать;
- печатать мусор;
- ломаться только иногда.

Примеры:

```cpp
delete p;
delete p; // двойное освобождение
```

```cpp
delete p;
std::cout << *p; // использование после delete
```

`delete nullptr` безопасен:

```cpp
int* p = nullptr;

delete p; // корректно, ничего не делает
```

Поэтому такой код корректен:

```cpp
delete p;
p = nullptr;
delete p; // корректно, это delete nullptr
```

## new (std::nothrow)

Обычный `new` при ошибке бросает `std::bad_alloc`.

```cpp
int* p = new int(42);
```

`new (std::nothrow)` при ошибке возвращает `nullptr`.

```cpp
#include <new>

int main() {
    int* p = new (std::nothrow) int(42);
    if (p == nullptr) {
        return 1;
    }

    delete p;
}
```

## Переопределение operator new/delete

`operator new` и `operator delete` можно переопределять.

Важно: это не замена ключевых слов `new` и `delete`.

Ключевое слово `new` все равно делает две операции:

1. вызывает подходящий `operator new`, чтобы выделить память;
2. вызывает конструктор объекта.

Ключевое слово `delete` тоже делает две операции:

1. вызывает деструктор объекта;
2. вызывает подходящий `operator delete`, чтобы освободить память.

То есть переопределяется только часть про выделение и освобождение памяти.

## Глобальное переопределение

Можно заменить глобальные функции выделения памяти:

```cpp
#include <cstdlib>
#include <new>

void* operator new(std::size_t size) {
    if (void* p = std::malloc(size)) {
        return p;
    }
    throw std::bad_alloc();
}

void operator delete(void* p) noexcept {
    std::free(p);
}
```

Теперь обычный `new T` будет использовать этот `operator new`.

Пример:

```cpp
struct User {
    User(int id) {}
    ~User() {}
};

int main() {
    User* user = new User(42);

    delete user;
}
```

Схема:

```text
new User(42)
    -> operator new(sizeof(User))
    -> User::User(42)

delete user
    -> User::~User()
    -> operator delete(user)
```

## Переопределение для класса

Чаще `operator new/delete` задают не глобально, а для конкретного класса.

```cpp
#include <cstdlib>
#include <new>

struct User {
    int id;

    User(int id)
        : id(id) {
    }

    static void* operator new(std::size_t size) {
        if (void* p = std::malloc(size)) {
            return p;
        }
        throw std::bad_alloc();
    }

    static void operator delete(void* p) noexcept {
        std::free(p);
    }
};

int main() {
    User* user = new User(42);

    delete user;
}
```

Для `new User(42)` сначала ищется `User::operator new`.

Если его нет, используется глобальный `::operator new`.

## Если конструктор бросил исключение

Если `operator new` выделил память, но конструктор бросил исключение, C++ сам вызовет подходящий `operator delete`.

```cpp
#include <cstdlib>
#include <new>
#include <stdexcept>

struct User {
    User() {
        throw std::runtime_error("fail");
    }

    static void* operator new(std::size_t size) {
        if (void* p = std::malloc(size)) {
            return p;
        }
        throw std::bad_alloc();
    }

    static void operator delete(void* p) noexcept {
        std::free(p);
    }
};

int main() {
    try {
        User* user = new User();
    } catch (...) {
    }
}
```

Память не утечет: конструктор не завершился, но выделенная память будет освобождена.

## operator new[]/delete[]

Для массивов нужны отдельные функции:

```cpp
#include <cstdlib>
#include <new>

struct User {
    static void* operator new[](std::size_t size) {
        if (void* p = std::malloc(size)) {
            return p;
        }
        throw std::bad_alloc();
    }

    static void operator delete[](void* p) noexcept {
        std::free(p);
    }
};

int main() {
    User* users = new User[3];

    delete[] users;
}
```

`new[]` ищет `operator new[]`.

`delete[]` ищет `operator delete[]`.

`operator new` и `operator new[]` - разные функции.

## Sized delete

У `operator delete` может быть версия с размером:

```cpp
#include <cstdlib>
#include <cstddef>

void operator delete(void* p, std::size_t size) noexcept {
    std::free(p);
}
```

Компилятор может выбрать такую форму, если размер удаляемого объекта известен.

Для класса это выглядит так:

```cpp
#include <cstdlib>
#include <cstddef>

struct User {
    static void operator delete(void* p, std::size_t size) noexcept {
        std::free(p);
    }
};
```

Параметр `size` полезен для своих аллокаторов и пулов памяти.

## Aligned new/delete

Для типов с большим выравниванием может использоваться форма с `std::align_val_t`.

```cpp
#include <cstdlib>
#include <new>

struct alignas(64) CacheLine {
    int value;
};

void* operator new(std::size_t size, std::align_val_t alignment) {
    void* p = nullptr;
    std::size_t align = static_cast<std::size_t>(alignment);

    if (posix_memalign(&p, align, size) == 0) {
        return p;
    }
    throw std::bad_alloc();
}

void operator delete(void* p, std::align_val_t) noexcept {
    std::free(p);
}
```

Обычно вручную это не пишут. Важно знать, что для over-aligned типов есть отдельная форма `operator new/delete`.

## Placement operator new

Placement new тоже выглядит как `operator new`, но не выделяет память.

Стандартная форма:

```cpp
void* operator new(std::size_t size, void* p) noexcept;
```

Именно она используется здесь:

```cpp
struct User {
    User(int id) {}
    ~User() {}
};

alignas(User) std::byte buffer[sizeof(User)];

User* user = new (buffer) User(42);
```

После placement new объект нужно разрушить вручную:

```cpp
user->~User();
```

В современном C++ для этого чаще используют обертки из `<memory>`:

```cpp
#include <cstddef>
#include <memory>

alignas(User) std::byte buffer[sizeof(User)];
auto* place = reinterpret_cast<User*>(buffer);

User* user = std::construct_at(place, 42);
std::destroy_at(user);
```

`std::construct_at` создает объект в уже выделенной памяти. По смыслу это безопасная стандартная обертка над placement new:

```cpp
std::construct_at(place, 42);
// примерно то же:
new (place) User(42);
```

Если у типа перегружен `operator&`, обычный `&obj` может вернуть не адрес. Тогда нужен `std::addressof`:

```cpp
#include <cstddef>
#include <cstdint>
#include <memory>

struct AlignedStruct {
    std::int32_t a;
    std::int64_t b;

    std::int64_t operator&() const {
        return a + b;
    }
};

alignas(AlignedStruct)
std::byte raw_memory_buffer[sizeof(AlignedStruct) * 5];

auto* array = reinterpret_cast<AlignedStruct*>(raw_memory_buffer);

// Не работает: operator& переопределен.
// auto* obj1 = std::construct_at(&array[0], 4, 2);

auto* obj2 = std::construct_at(std::addressof(array[0]), 4, 2);
std::destroy_at(obj2);
```

`std::destroy_at` вызывает деструктор объекта:

```cpp
std::destroy_at(user);
// примерно то же:
user->~User();
```

Такую стандартную placement-форму обычно не переопределяют.

## Правила

- Если переопределяешь `operator new`, рядом нужен совместимый `operator delete`.
- Для массивов отдельно: `operator new[]` и `operator delete[]`.
- `operator new` должен вернуть правильно выровненную память или бросить исключение.
- Обычный throwing `operator new` не должен возвращать `nullptr`.
- `operator delete` должен быть `noexcept`.
- Нельзя смешивать разные способы выделения и освобождения памяти.
- Для placement new в современном коде можно использовать `std::construct_at` и `std::destroy_at`.
- `alignas(N)` задает выравнивание в байтах, `alignas(T)` - выравнивание как у типа `T`.

## Саммари

- `malloc/free` работают с сырыми байтами.
- `new/delete` работают с C++-объектами.
- `new` выделяет память и создает объект.
- `delete` уничтожает объект и освобождает память.
- Placement new создает объект в уже выделенной памяти.
- Placement new можно использовать и в динамической памяти, и в стековом буфере.
- Placement new не освобождает память и не выделяет ее.
- После placement new деструктор обычно вызывается вручную.
- `std::construct_at` и `std::destroy_at` - стандартные обертки-помощники для создания и разрушения объекта в сырой памяти.
- `std::addressof` получает настоящий адрес объекта, даже если `operator&` перегружен.
- Для стекового буфера под объект нужно учитывать выравнивание: `alignas(T)`.
- `alignas` задает выравнивание явно, `alignof(T)` возвращает требуемое выравнивание типа `T`.
- `alignof(std::max_align_t)` задает максимальное выравнивание для базовых типов.
- Обычная динамическая память выровнена минимум под `alignof(std::max_align_t)`, стековая память - по типу объявленного объекта.
- Для доступа к объекту, созданному placement new в `std::byte[]`, нужен указатель нужного типа, обычно через `reinterpret_cast`.
- Нельзя читать объект через несовместимый тип: это нарушение strict aliasing.
- `new[]` создает массив, освобождать нужно только через `delete[]`.
- У `new[]` может быть служебный array cookie/count перед массивом.
- Нельзя смешивать пары: `malloc/free`, `new/delete`, `new[]/delete[]`.
- `malloc` при ошибке возвращает `nullptr`.
- `new` и `::operator new` при ошибке бросают `std::bad_alloc`.
- `new (std::nothrow)` при ошибке возвращает `nullptr`.
- `operator new/delete` можно переопределять глобально или для класса.
- Ключевое слово `new` вызывает `operator new`, а потом конструктор.
- Ключевое слово `delete` вызывает деструктор, а потом `operator delete`.
- Для массивов используются отдельные `operator new[]/delete[]`.
- Если конструктор бросил исключение, C++ вызовет подходящий `operator delete`.
- `operator delete` может получать размер объекта: sized delete.
- Для over-aligned типов есть формы с `std::align_val_t`.
- Забыл `delete` - получил утечку памяти.
- Использовал указатель после `delete` - получил undefined behavior.
- `delete nullptr` корректен и ничего не делает.
- Undefined behavior означает, что стандарт C++ ничего не гарантирует.
