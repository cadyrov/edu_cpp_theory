# 6. Правила нуля, трех и пяти

## Суть

Эти правила отвечают на вопрос: что делать со специальными функциями класса, если класс владеет ресурсом.

Специальные функции:

- деструктор;
- copy constructor;
- copy assignment;
- move constructor;
- move assignment.

## Правило нуля

Лучший вариант: класс сам не управляет ресурсом вручную.

Ресурсом управляет готовый RAII-тип:

- `std::unique_ptr`;
- `std::vector`;
- `std::string`;
- `std::fstream`.

```cpp
#include <memory>

class User {
public:
    explicit User(int id)
        : id_(std::make_unique<int>(id)) {
    }

private:
    std::unique_ptr<int> id_;
};
```

Мы не пишем:

- деструктор;
- copy constructor;
- copy assignment;
- move constructor;
- move assignment.

Компилятор и поля класса сами задают правильное поведение.

## Правило трех

Если класс вручную управляет ресурсом и ему нужен деструктор, скорее всего нужны еще копирование и присваивание.

Три функции:

- destructor;
- copy constructor;
- copy assignment.

Плохой пример:

```cpp
class Buffer {
public:
    explicit Buffer(int size)
        : size_(size), data_(new int[size]) {
    }

    ~Buffer() {
        delete[] data_;
    }

private:
    int size_ = 0;
    int* data_ = nullptr;
};
```

Проблема:

```cpp
Buffer a(10);
Buffer b = a; // копируется только указатель
```

Теперь `a` и `b` указывают на один массив.

В конце будет двойной `delete[]`.

## Правильное копирование

```cpp
#include <algorithm>

class Buffer {
public:
    explicit Buffer(int size)
        : size_(size), data_(new int[size]) {
    }

    ~Buffer() {
        delete[] data_;
    }

    Buffer(const Buffer& other)
        : size_(other.size_), data_(new int[other.size_]) {
        std::copy(other.data_, other.data_ + size_, data_);
    }

    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            int* new_data = new int[other.size_];
            std::copy(other.data_, other.data_ + other.size_, new_data);

            delete[] data_;

            size_ = other.size_;
            data_ = new_data;
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
Buffer(const Buffer& other)
```

Создает независимую копию ресурса.

```cpp
operator=(const Buffer& other)
```

Сначала готовит новый ресурс, потом удаляет старый.

## Правило пяти

В C++11 появились move constructor и move assignment.

Если класс вручную управляет ресурсом, обычно нужны пять функций:

- destructor;
- copy constructor;
- copy assignment;
- move constructor;
- move assignment.

```cpp
#include <algorithm>
#include <utility>

class Buffer {
public:
    explicit Buffer(int size)
        : size_(size), data_(new int[size]) {
    }

    ~Buffer() {
        delete[] data_;
    }

    Buffer(const Buffer& other)
        : size_(other.size_), data_(new int[other.size_]) {
        std::copy(other.data_, other.data_ + size_, data_);
    }

    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            Buffer temp(other);
            swap(temp);
        }

        return *this;
    }

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

    void swap(Buffer& other) noexcept {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

private:
    int size_ = 0;
    int* data_ = nullptr;
};
```

## Что выбрать

Предпочтительно:

```cpp
class Buffer {
private:
    std::vector<int> data_;
};
```

Это правило нуля.

Если можно не писать специальные функции вручную, лучше их не писать.

## Что будет выведено

```cpp
#include <iostream>
#include <memory>

struct User {
    User() {
        std::cout << "ctor\n";
    }

    ~User() {
        std::cout << "dtor\n";
    }
};

int main() {
    std::unique_ptr<User> p = std::make_unique<User>();
}
```

Вывод:

```text
ctor
dtor
```

Разбор: деструктор `User` вызывается автоматически, потому что `unique_ptr` владеет объектом.

## Частые ошибки

### Написали деструктор, забыли копирование

```cpp
class A {
public:
    A() : p_(new int(42)) {}
    ~A() { delete p_; }

private:
    int* p_ = nullptr;
};
```

Копирование такого класса опасно.

### Написали copy, забыли move

Класс будет работать, но может быть менее эффективным.

### Вручную управляют памятью, хотя можно использовать готовый тип

```cpp
int* data_;
```

Чаще лучше:

```cpp
std::vector<int> data_;
```

## Саммари

- Правило нуля: не управляй ресурсом вручную.
- Правило нуля обычно лучший вариант.
- Правило трех: если нужен деструктор, часто нужны copy constructor и copy assignment.
- Правило пяти: к правилу трех добавляются move constructor и move assignment.
- Ручной ресурс требует явного решения: копировать, перемещать или запретить.
- `std::unique_ptr`, `std::vector`, `std::string` помогают не писать специальные функции вручную.
