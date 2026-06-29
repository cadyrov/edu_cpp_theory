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

```cpp
template <typename T>
void foo(T x) {}

const int a = 10;
foo(a); // T = int

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

`const T&` нужно читать как "ссылка на const-версию всего `T`".

```cpp
template <typename T>
void foo(const T& x) {}

int value = 10;
int* const p = &value;

foo(p); // T = int*, параметр int* const&
```

Если `T = int*`, то `const T&` дает `int* const&`, а не `const int*&`.

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

## Саммари

- Шаблон функции создает функции для разных типов.
- `typename` и `class` в параметрах шаблона почти одно и то же.
- Тип часто выводится из аргументов.
- Если тип нельзя вывести, его указывают явно.
- Форма параметра (`T`, `T&`, `const T&`, `T&&`, `T*`) определяет правила вывода `T`.
- Шаблоны обычно размещают в заголовочных файлах.
- Ошибки в шаблоне часто появляются только при конкретном использовании.
