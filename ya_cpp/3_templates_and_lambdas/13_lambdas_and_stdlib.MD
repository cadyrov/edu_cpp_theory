# 13. Лямбда-выражения и стандартная библиотека

## Суть

Лямбда - короткий функциональный объект прямо в месте использования.

```cpp
auto f = [](int x) {
    return x * 2;
};
```

В стандартной библиотеке лямбды часто передают в алгоритмы.

```cpp
std::sort(v.begin(), v.end(), [](int a, int b) {
    return a > b;
});
```

## Примеры

### Пример 1: простая лямбда

```cpp
auto square = [](int x) {
    return x * x;
};

int y = square(5);
```

### Пример 2: захват переменной

```cpp
int limit = 10;

auto less_than_limit = [limit](int x) {
    return x < limit;
};
```

`limit` захвачен по значению.

### Пример 3: алгоритм стандартной библиотеки

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> v{3, 1, 2};

    std::sort(v.begin(), v.end(), [](int a, int b) {
        return a < b;
    });
}
```

### Пример 4: поиск

```cpp
auto it = std::find_if(v.begin(), v.end(), [](int x) {
    return x % 2 == 0;
});
```

## Подводные камни

Захват по ссылке опасен, если лямбда живет дольше переменной.

```cpp
auto make_filter() {
    int limit = 10;

    return [&limit](int x) {
        return x < limit;
    }; // ошибка: ссылка на мертвую переменную
}
```

Захват по значению копирует объект.

```cpp
std::vector<int> data;

auto f = [data] {
    return data.size();
};
```

Для больших объектов это может быть дорого.

По умолчанию `operator()` у лямбды `const`, поэтому копии, захваченные по
значению, менять нельзя.

```cpp
auto id_generator = [current = 0]() {
    return ++current; // ошибка
};
```

`mutable` делает `operator()` неконстантным и разрешает менять внутреннюю копию.

```cpp
auto id_generator = [current = 0]() mutable {
    return ++current;
};

std::cout << id_generator() << '\n'; // 1
std::cout << id_generator() << '\n'; // 2
```

Оригинальная переменная при захвате по значению все равно не изменяется.

## Саммари

- Лямбда создает объект с `operator()`.
- Захват `[]` управляет доступом к внешним переменным.
- `[x]` копирует, `[&x]` берет ссылку.
- Лямбды удобно передавать в алгоритмы STL.
- Захват по ссылке опасен при долгой жизни лямбды.
- `mutable` меняет только копии внутри лямбды.
