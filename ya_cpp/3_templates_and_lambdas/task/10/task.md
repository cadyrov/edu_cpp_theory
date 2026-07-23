Если вы собираетесь использовать трейт has_size<T> только, когда нужно булевское значение, то не обязательно подражать стандартной библиотеке и применять шаблон класса — подойдёт и шаблонная переменная. При выборе частичной специализации шаблона переменной SFINAE действует как и при выборе шаблона класса.
- Вот полный пример использования has_size_v:
```cpp
#include <print>
#include <utility>

double f(double) {
    std::println("f(double)");
    return {};
}

template <typename Container, std::enable_if_t<has_size_v<Container>>* = nullptr>
auto f(Container const &cont) {
    std::println("f(Container const&)");
    return cont.size();
}

struct S {
    int size() const { return 43; }
};

int main() {
    auto x = f(42);
    auto y = f(S{});
} 
```

Скопируйте код ниже к себе и реализуйте шаблонную переменную has_size_v, чтобы код из примера выше компилировался и печатал следующий результат:

```cpp
f(double)
f(Container const&) 
```
Используйте для этого частичную специализацию шаблона переменной.

```cpp
template <typename T, typename = void>
// Здесь первичный шаблон булевской переменной has_size_v

template <typename T>
// А здесь частичная специализация шаблона переменной has_size_v 
```

- Посмотрите, как мы реализовывали has_size_v, когда хотели сделать более удобной работу с has_size.
- Первичный шаблон должен определять констатную переменную has_size_v со значением false.
- Посмотрите на реализацию частичной специализации шаблонного класса has_size.
- Частичная специализация константной переменной has_size_v должна иметь значение true.