# 7. Идеальная передача и auto

## Суть

Идеальная передача сохраняет категорию значения: lvalue остается lvalue, rvalue остается rvalue.

Для этого используют forwarding reference и `std::forward`.

```cpp
template <typename T>
void wrapper(T&& value) {
    target(std::forward<T>(value));
}
```

`auto` выводит тип по похожим правилам, но не всегда сохраняет ссылки и `const`.

## Примеры

### Пример 1: forwarding reference

```cpp
#include <utility>

void use(int& x);
void use(int&& x);

template <typename T>
void call_use(T&& x) {
    use(std::forward<T>(x));
}

int main() {
    int a = 10;
    call_use(a);  // use(int&)
    call_use(10); // use(int&&)
}
```

### Пример 2: auto

```cpp
const int x = 10;

auto a = x;        // int
const auto b = x;  // const int
auto& c = x;       // const int&
```

### Пример 3: decltype(auto)

```cpp
int value = 10;

int& get() {
    return value;
}

decltype(auto) x = get(); // int&
```

## Подводные камни

`T&&` является forwarding reference только если `T` выводится.

```cpp
template <typename T>
void foo(T&& x); // forwarding reference

void bar(int&& x); // обычная rvalue-ссылка
```

`std::move` всегда превращает в rvalue.

```cpp
use(std::move(x));
```

`std::forward` делает это условно, по `T`.

```cpp
use(std::forward<T>(x));
```

`auto` при копировании теряет ссылку.

```cpp
int a = 10;
int& r = a;

auto x = r; // int, не int&
```

Чтобы сохранить ссылку, нужен `auto&` или `decltype(auto)`.

## Саммари

- Идеальная передача сохраняет lvalue/rvalue.
- Для нее нужны `T&&` и `std::forward<T>`.
- `std::move` не передает идеально, а всегда двигает.
- `auto` часто убирает ссылки и верхнеуровневый `const`.
- `auto&` сохраняет ссылку.
- `decltype(auto)` сохраняет точный тип выражения.

