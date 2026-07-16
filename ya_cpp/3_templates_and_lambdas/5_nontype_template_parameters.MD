# 5. Шаблонные параметры, не являющиеся типами

## Суть

Параметр шаблона может быть не типом, а значением.

```cpp
template <typename T, std::size_t N>
struct Array {
    T data[N];
};
```

`Array<int, 3>` и `Array<int, 5>` - разные типы.

## Примеры

### Пример 1: размер массива

```cpp
#include <cstddef>

template <typename T, std::size_t N>
struct StaticArray {
    T data[N];

    std::size_t size() const {
        return N;
    }
};

int main() {
    StaticArray<int, 4> a{};
}
```

### Пример 2: значение как параметр

```cpp
template <int Limit>
bool in_range(int x) {
    return x >= 0 && x < Limit;
}

int main() {
    bool ok = in_range<10>(7);
}
```

### Пример 3: ссылка на объект

```cpp
extern const int default_value;

template <const int& Value>
int get() {
    return Value;
}
```

### Пример 4: callback на этапе компиляции

Обычный вариант хранит указатель на функцию в объекте.

```cpp
struct Class {
    explicit Class(void (*callback)())
        : callback_(callback) {}

    void foo() {
        callback_();
    }

    void (*callback_)();
};
```

Если callback не меняется после создания объекта, его можно сделать нетиповым параметром шаблона.

```cpp
template <void (*Callback)()>
struct Class {
    void foo() {
        Callback();
    }
};
```

Использование:

```cpp
#include <iostream>

void hello() {
    std::cout << "hello\n";
}

void bye() {
    std::cout << "bye\n";
}

int main() {
    Class<hello> a;
    Class<bye> b;

    a.foo(); // hello
    b.foo(); // bye
}
```

`Callback` известен на этапе компиляции.
Объекту не нужно хранить указатель на функцию внутри себя.

### Пример 5: шаблон как параметр

Параметром шаблона может быть не только тип или значение, но и другой шаблон.

```cpp
template <template <typename> typename Container>
struct Wrapper {
    Container<int> data;
};
```

Здесь `Container` - это не готовый тип, а шаблон, которому потом передают `int`.

```cpp
Wrapper<std::vector> w;
```

Такой параметр называют `template template parameter`.
Он нужен, когда код должен работать не с конкретным типом вроде `std::vector<int>`,
а с самим шаблоном вроде `std::vector`.

Правила:

- Сигнатура должна совпадать: количество и вид параметров передаваемого шаблона должны подходить под объявление.
- В шаблон-шаблонный параметр передают первичный шаблон, а не его полную или частичную специализацию.
- Если объявлено `template <template <typename> typename C>`, ожидается шаблон с одним типовым параметром.
- Шаблон с нетиповым параметром можно принять только если это явно указано в сигнатуре.
- В этом контексте `typename` и `class` эквивалентны.

```cpp
template <template <int> typename C>
struct WrapperByInt {
    C<10> data;
};
```

## Подводные камни

Значение должно быть известно на этапе компиляции.

```cpp
int n = 10;
StaticArray<int, n> a; // ошибка
```

Нужно использовать константное выражение.

```cpp
constexpr int n = 10;
StaticArray<int, n> a;
```

Разные значения создают разные типы.

```cpp
StaticArray<int, 3> a;
StaticArray<int, 4> b;

a = b; // ошибка
```

Большое количество разных значений может увеличить время компиляции и размер кода.

Нетиповые параметры удобны, но они переносят часть данных в тип.

Разные callback создают разные типы.

```cpp
Class<hello> a;
Class<bye> b;

a = b; // ошибка: разные типы
```

Если callback нужно менять во время выполнения, лучше хранить указатель или `std::function` в объекте.

## Саммари

- Нетиповой параметр шаблона - это значение, а не тип.
- Значение должно быть известно во время компиляции.
- Частый пример - размер статического массива.
- Нетиповым параметром может быть указатель на функцию.
- Шаблон тоже может быть параметром другого шаблона: `template <template <typename> typename C>`.
- Разные значения обычно создают разные типы.
- Это удобно для проверок и оптимизаций на этапе компиляции.
- Цена - больше разных инстанцирований шаблона.
