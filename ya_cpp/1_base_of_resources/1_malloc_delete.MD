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

## Саммари

- `malloc/free` работают с сырыми байтами.
- `new/delete` работают с C++-объектами.
- `new` выделяет память и создает объект.
- `delete` уничтожает объект и освобождает память.
- `malloc` при ошибке возвращает `nullptr`.
- `new` и `::operator new` при ошибке бросают `std::bad_alloc`.
- Забыл `delete` - получил утечку памяти.
- Использовал указатель после `delete` - получил undefined behavior.
