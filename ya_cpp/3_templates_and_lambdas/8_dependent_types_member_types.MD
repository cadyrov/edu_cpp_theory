# 8. Зависимые типы и member types

## Суть

Класс может объявлять вложенные типы.

```cpp
std::vector<int>::value_type; // int
std::vector<int>::size_type;  // тип размера
std::vector<int>::reference;  // int&
```

Такие типы часто называют member types.

В шаблоне тип контейнера неизвестен заранее.

```cpp
template <typename Container>
void foo(Container& c) {
    typename Container::value_type x{};
}
```

`Container::value_type` зависит от параметра шаблона `Container`, поэтому это зависимый тип.

`typename` нужен, чтобы компилятор понял: `Container::value_type` - это тип, а не статическое поле.

## Примеры

### Пример 1: зависимый тип

```cpp
template <typename Container>
typename Container::value_type first_value(const Container& c) {
    return c.front();
}
```

Без `typename` код не скомпилируется.

```cpp
template <typename Container>
Container::value_type first_value(const Container& c); // ошибка
```

### Пример 2: проверка совпадения типов

```cpp
template <typename T1, typename T2>
struct SameType {};

template <typename T>
struct SameType<T, T> {
    using type = T;
};
```

`SameType<T1, T2>::type` существует только когда `T1` и `T2` - один и тот же тип.

```cpp
SameType<int, int>::type;    // int
SameType<int, double>::type; // ошибки: type нет
```

`typename` перед `SameType<...>::type` нужен, если это имя используется как тип.

```cpp
#include <array>

template <typename T1, typename T2>
struct SameType {};

template <typename T>
struct SameType<T, T> {
    using type = T;
};

using IsArraysSame =
    typename SameType<std::array<int, 5>, std::array<int, 6>>::type;
```

Этот код не скомпилируется.

`std::array<int, 5>` и `std::array<int, 6>` - разные типы, потому что размер входит в тип `std::array`.

Значит выбирается основной шаблон:

```cpp
template <typename T1, typename T2>
struct SameType {};
```

А в нем нет вложенного типа `type`.

Рабочий вариант:

```cpp
using IsArraysSame =
    typename SameType<std::array<int, 5>, std::array<int, 5>>::type;
```

Тут оба типа одинаковые, поэтому выбирается частичная специализация `SameType<T, T>`, где `type` существует.

### Пример 3: стек поверх контейнера

```cpp
#include <deque>
#include <utility>

template <typename T1, typename T2>
struct SameType {};

template <typename T>
struct SameType<T, T> {
    using type = T;
};

template <
    typename T,
    typename Container = std::deque<T>,
    typename = typename SameType<T, typename Container::value_type>::type
>
class Stack {
public:
    using value_type = typename Container::value_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using size_type = typename Container::size_type;

    Stack() = default;

    template <typename It>
    Stack(It first, It second)
        : storage_(first, second) {}

    void push(const value_type& value) {
        storage_.push_back(value);
    }

    void push(value_type&& value) {
        storage_.push_back(std::move(value));
    }

    void pop() {
        storage_.pop_back();
    }

    reference top() {
        return storage_.back();
    }

    const_reference top() const {
        return storage_.back();
    }

    bool empty() const {
        return storage_.empty();
    }

    size_type size() const {
        return storage_.size();
    }

private:
    Container storage_;
};
```

Здесь:

- `Container::value_type`, `Container::reference`, `Container::size_type` - зависимые типы.
- `typename` перед ними обязателен.
- `SameType<T, typename Container::value_type>::type` проверяет, что стек хранит тот же тип, что и контейнер.
- `It` - параметр только конструктора, а не всего класса.

### Пример 4: использование стека

```cpp
#include <vector>
#include <deque>

std::vector<int> values{1, 2, 3};

Stack<int> s1;
Stack<int> s2(values.begin(), values.end());
Stack<int, std::vector<int>> s3(values.begin(), values.end());
```

Так можно заменить внутренний контейнер, но внешний интерфейс останется тем же.

```cpp
Stack<int>::size_type n = s2.size();
Stack<int>::reference top = s2.top();
```

`size()` возвращает тип размера внутреннего контейнера.

`top()` возвращает правильный тип ссылки на элемент.

Такой код не должен компилироваться:

```cpp
Stack<int, std::vector<double>> bad;
```

`T = int`, но `Container::value_type = double`.
Проверка через `SameType` запрещает такую несовместимую пару.

## Подводные камни

`typename` нужен только перед зависимым именем типа.

```cpp
typename Container::value_type x{}; // нужно
std::vector<int>::value_type y{};   // typename не нужен
```

Если забыть `typename`, компилятор не знает, тип это или значение.

```cpp
template <typename Container>
void foo() {
    Container::value_type x{}; // ошибка
}
```

Шаблонный конструктор внутри шаблонного класса имеет свой отдельный список параметров.

```cpp
template <typename T, typename Container>
class Stack {
public:
    template <typename It>
    Stack(It first, It second);
};
```

Если определять его снаружи класса, нужны два `template`.

```cpp
template <typename T, typename Container>
template <typename It>
Stack<T, Container>::Stack(It first, It second)
    : storage_(first, second) {}
```

Если сделать `It` параметром класса, это будет другой смысл.

```cpp
template <typename T, typename Container, typename It>
class Stack {};
```

Тогда стек из `std::vector<int>::iterator` и стек из `std::deque<int>::iterator` будут разными типами, хотя итератор нужен только для конструктора.

## Саммари

- Member types - это вложенные типы класса, например `Container::value_type`.
- Зависимый тип зависит от параметра шаблона.
- Для зависимых типов нужен `typename`.
- Member types позволяют писать интерфейс, согласованный с внутренним контейнером.
- Шаблонный конструктор может иметь свои параметры, отдельные от параметров класса.
- Через зависимые типы можно проверять совместимость шаблонных параметров.
