# 1. Шаблоны функций

## Суть

Шаблон функции описывает не одну функцию, а правило для создания функций.

```cpp
template <typename T>
T max_value(T a, T b) {
    return a < b ? b : a;
}
```

Компилятор сам создает нужную версию функции по типам аргументов.

```cpp
max_value(1, 2);       // T = int
max_value(1.5, 2.5);   // T = double
```

## Примеры

### Пример 1: один тип

```cpp
template <typename T>
T square(T x) {
    return x * x;
}

int main() {
    int a = square(5);
    double b = square(1.5);
}
```

### Пример 2: несколько типов

```cpp
template <typename T, typename U>
auto add(T a, U b) {
    return a + b;
}

int main() {
    auto x = add(1, 2.5); // double
}
```

### Пример 3: явное указание типа

```cpp
template <typename T>
T make_zero() {
    return T{};
}

int main() {
    auto x = make_zero<int>();
}
```

### Пример 4: как читать вывод типа

Вывод `T` зависит от формы параметра.

```cpp
template <typename T>
void by_value(T x);        // копия

template <typename T>
void by_ref(T& x);         // lvalue-ссылка

template <typename T>
void by_const_ref(const T& x);

template <typename T>
void by_forward_ref(T&& x);

template <typename T>
void by_pointer(T* x);
```

Основные правила:

- `T x` убирает ссылку, верхнеуровневый `const`, массив превращает в указатель.
- `T& x` сохраняет `const` объекта и массив, но сама ссылка не входит в `T`.
- `const T& x` не включает внешний `const` в `T`.
- `T&& x` в шаблоне является forwarding reference: для lvalue `T` становится ссылкой, для rvalue - обычным типом.
- `T* x` выводит `T` как тип под указателем.

Важно различать `const` у самого указателя и у объекта, на который он указывает.
При передаче по значению `const` самого указателя теряется, а `const` объекта сохраняется.
При передаче по ссылке сохраняется и `const` самого указателя.

```cpp
template <typename T>
void foo(T x) {}

const int a = 10;
foo(a); // T = int

const int* p1 = &a;
foo(p1); // T = const int*

int value = 10;
int* const p2 = &value;
foo(p2); // T = int*

int arr[3]{};
foo(arr); // T = int*
```

```cpp
template <typename T>
void foo(T& x) {}

const int a = 10;
foo(a); // T = const int

int arr[3]{};
foo(arr); // T = int[3]
```

```cpp
template <typename T>
void foo(T& x) {}

int value = 10;
int* const p = &value;

foo(p); // T = int* const
```

`const T&` нужно читать как "ссылка на const-версию всего `T`".

```cpp
template <typename T>
void foo(const T& x) {}

int value = 10;
int* const p = &value;

foo(p); // T = int*, параметр int* const&
```

Если `T = int*`, то `const T&` дает `int* const&`, а не `const int*&`.

Forwarding reference работает только когда `T` выводится в этом вызове.
В нешаблонном методе шаблонного класса `T&&` - обычная rvalue-ссылка.

```cpp
template <typename T>
struct Box {
    void set(T&& value); // не forwarding reference
};

Box<int> b;
int x = 1;
// b.set(x); // ошибка: int&& не принимает lvalue
```

Если параметр имеет форму шаблонного класса, `T` выводится из его аргумента.

```cpp
#include <vector>

template <typename T>
void read_vector(const std::vector<T>& values) {}

std::vector<int> v;
read_vector(v); // T = int
```

Для одного `T` все аргументы должны дать согласованный результат.

## Подводные камни

Шаблон должен быть виден в месте использования. Поэтому шаблоны обычно пишут в `.hpp`.

```cpp
// foo.hpp
template <typename T>
T foo(T x) {
    return x;
}
```

Типы аргументов должны подходить под тело шаблона.

```cpp
template <typename T>
T twice(T x) {
    return x + x;
}
```

Если для `T` нет `operator+`, код не скомпилируется.

Вывод типа не делает неявное приведение между разными `T`.

```cpp
max_value(1, 2.5); // ошибка: T не может быть и int, и double
```

Можно указать тип явно:

```cpp
max_value<double>(1, 2.5);
```

То же бывает, когда один параметр ожидает, например, указатель, а другой - итератор:
единый `T` может не вывестись.

## Саммари

- Шаблон функции создает функции для разных типов.
- `typename` и `class` в параметрах шаблона почти одно и то же.
- Тип часто выводится из аргументов.
- Если тип нельзя вывести, его указывают явно.
- Форма параметра (`T`, `T&`, `const T&`, `T&&`, `T*`) определяет правила вывода `T`.
- По значению теряются ссылки и верхнеуровневый `const`.
- По ссылке сохраняется `const` объекта.
- `T&&` является forwarding reference только если `T` выводится в этом вызове.
- Из параметра вида `Template<T>` компилятор может вывести `T`.
- Шаблоны обычно размещают в заголовочных файлах.
- Ошибки в шаблоне часто появляются только при конкретном использовании.
