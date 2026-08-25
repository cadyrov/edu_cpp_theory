# 2. Перегрузка функций и вывод типов в шаблонах

## Суть

Перегрузка позволяет иметь несколько функций с одним именем, но разными параметрами.

```cpp
void print(int x);
void print(double x);
void print(const char* s);
```

Шаблон тоже участвует в перегрузке.

```cpp
template <typename T>
void print(T x) {
    std::cout << x << '\n';
}
```

Компилятор выбирает наиболее подходящую функцию.

## Примеры

### Пример 1: обычная перегрузка

```cpp
#include <iostream>

void log(int x) {
    std::cout << "int: " << x << '\n';
}

void log(double x) {
    std::cout << "double: " << x << '\n';
}

int main() {
    log(10);
    log(1.5);
}
```

### Пример 2: шаблон и обычная функция

```cpp
#include <iostream>

void print(int x) {
    std::cout << "int\n";
}

template <typename T>
void print(T x) {
    std::cout << "template\n";
}

int main() {
    print(1);    // int
    print(1.5);  // template
}
```

Если обычная функция подходит точно, она обычно выигрывает у шаблона.

### Пример 3: вывод типа

```cpp
template <typename T>
void foo(T x) {}

int main() {
    foo(1);      // T = int
    foo(1.5);    // T = double
    foo("abc");  // T = const char*
}
```

### Пример 4: ссылка сохраняет const

```cpp
template <typename T>
void foo(const T& x) {}

int main() {
    const int value = 10;
    foo(value); // T = int, параметр const int&
}
```

## Подводные камни

Вывод типа идет по каждому аргументу отдельно.

```cpp
template <typename T>
T max_value(T a, T b) {
    return a < b ? b : a;
}

max_value(1, 2.5); // ошибка
```

Компилятор не может выбрать один `T`: первый аргумент дает `int`, второй - `double`.

Можно указать тип явно:

```cpp
max_value<double>(1, 2.5);
```

Передача по значению убирает верхнеуровневый `const`.

```cpp
template <typename T>
void foo(T x) {}

const int a = 10;
foo(a); // T = int
```

Массивы и функции при передаче по значению превращаются в указатели.

```cpp
template <typename T>
void foo(T x) {}

int arr[3]{};
foo(arr); // T = int*
```

Слишком общий шаблон может перехватить вызов.

```cpp
template <typename T>
void process(T x) {}

void process(long x) {}

process(1); // шаблон: T = int
```

## Саммари

- Перегрузка выбирает лучшую функцию по аргументам.
- Шаблоны участвуют в перегрузке вместе с обычными функциями.
- Обычная функция выигрывает, если подходит не хуже шаблона.
- Тип шаблона часто выводится из аргументов.
- Для одного `T` все аргументы должны согласоваться.
- Передача по значению теряет верхнеуровневый `const`.
- Массивы при передаче по значению превращаются в указатели.
