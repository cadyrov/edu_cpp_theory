# 2. Метапрограммирование с `std::tuple`

## Суть

`std::tuple` хранит набор значений, типы и количество которых известны на этапе компиляции. Поэтому кортеж удобно использовать как compile-time список типов и преобразовывать через вариативные шаблоны.

Основные инструменты:

- `std::get<I>` — доступ к элементу по compile-time индексу;
- `std::tuple_size_v<T>` — число элементов;
- `std::tuple_element_t<I, T>` — тип элемента;
- fold expressions — применение оператора ко всей пачке параметров;
- `std::index_sequence` — пачка compile-time индексов;
- `std::tuple_cat` — объединение кортежей.

## Как устроен `std::tuple`

В libstdc++ кортеж реализован через рекурсивное наследование: каждому элементу соответствуют индекс и базовый класс, хранящий значение.

Упрощённая схема:

```cpp
TupleImpl<0, int, double, char>
    -> TupleImpl<1, double, char>
        -> TupleImpl<2, char>
```

`std::get<1>(tuple)` на этапе компиляции выбирает ветку с индексом `1`. Поиска или цикла во время выполнения нет.

Пустые типы могут храниться без увеличения размера благодаря оптимизациям вроде `[[no_unique_address]]`.

> Конкретное устройство — деталь реализации стандартной библиотеки. Другие реализации могут быть устроены иначе.

## Fold expressions

Свёртки появились в C++17 и раскрывают пачку параметров без ручной рекурсии.

```cpp
template <typename... Args>
constexpr auto Sum(Args... args) {
    return (... + args);
}
```

Четыре формы:

```cpp
(... op pack)       // унарная левая
(pack op ...)       // унарная правая
(init op ... op pack) // бинарная левая
(pack op ... op init) // бинарная правая
```

Свёртка по запятой удобна для последовательного вызова операции:

```cpp
template <typename... Args>
void PrintAll(const Args&... args) {
    ((std::cout << args << ' '), ...);
}
```

Сложную логику лучше вынести в отдельную функцию или лямбду, оставив свёртку короткой.

## `std::index_sequence`

`std::make_index_sequence<N>` создаёт тип с индексами от `0` до `N - 1`. Пачку индексов можно раскрыть внутри `std::get`.

```cpp
template <std::size_t N, typename Tuple>
constexpr auto GetFirst(const Tuple& tuple) {
    static_assert(N <= std::tuple_size_v<Tuple>);

    return [&]<std::size_t... Is>(std::index_sequence<Is...>) {
        return std::tuple{std::get<Is>(tuple)...};
    }(std::make_index_sequence<N>{});
}
```

Явный список шаблонных параметров лямбды `[]<...>` требует C++20. В C++17 для распаковки обычно пишут отдельную шаблонную функцию-помощник.

## Перестановка элементов

Для разворота кортежа достаточно изменить формулу индекса:

```cpp
template <typename Tuple>
constexpr auto Reverse(const Tuple& tuple) {
    constexpr std::size_t size = std::tuple_size_v<Tuple>;

    return [&]<std::size_t... Is>(std::index_sequence<Is...>) {
        return std::tuple{std::get<size - 1 - Is>(tuple)...};
    }(std::make_index_sequence<size>{});
}
```

По тому же принципу реализуются `last_n`, перестановки и выбор элементов.

## Фильтрация по типам

Каждый элемент превращается либо в одноэлементный, либо в пустой кортеж. Затем результаты объединяются через `std::tuple_cat`.

```cpp
template <std::size_t I,
          template <typename> typename Predicate,
          typename Tuple>
constexpr auto ValueOrEmpty(const Tuple& tuple) {
    using Type = std::tuple_element_t<I, Tuple>;

    if constexpr (Predicate<Type>::value) {
        return std::tuple{std::get<I>(tuple)};
    } else {
        return std::tuple{};
    }
}

template <template <typename> typename Predicate, typename Tuple>
constexpr auto Filter(const Tuple& tuple) {
    constexpr std::size_t size = std::tuple_size_v<Tuple>;

    return [&]<std::size_t... Is>(std::index_sequence<Is...>) {
        return std::tuple_cat(ValueOrEmpty<Is, Predicate>(tuple)...);
    }(std::make_index_sequence<size>{});
}
```

Пример:

```cpp
std::tuple values{1, 2.5, 'a', "text"};
auto numbers = Filter<std::is_arithmetic>(values);
// std::tuple<int, double, char>
```

## Подводные камни

### 1. Направление свёртки влияет на результат

Для `+` это обычно незаметно, но важно для `-`, `/`, присваивания и пользовательских операторов.

### 2. Пустая пачка поддерживает не все операторы

У унарной свёртки стандартные значения для пустой пачки есть только у `&&`, `||` и `,`. Для остальных операторов задавайте начальное значение.

```cpp
return (0 + ... + args);
```

### 3. Примеры выше копируют элементы

`std::tuple{std::get<I>(tuple)...}` выводит типы значений. Для сохранения ссылок нужны `std::tie`, `std::forward_as_tuple` или явно заданные ссылочные типы.

### 4. Проверяйте индексы

`N > std::tuple_size_v<Tuple>` и вычисление `size - 1` для пустого кортежа приводят к ошибкам компиляции или переполнению беззнакового значения.

### 5. `tuple_cat` может копировать или перемещать элементы

Для тяжёлых и некопируемых объектов нужно внимательно выбирать ссылки и корректно передавать категорию значения.

## Саммари

- `std::tuple` можно использовать как список значений и типов времени компиляции.
- `std::get`, `tuple_size` и `tuple_element` дают доступ к структуре кортежа.
- Fold expressions раскрывают пачки параметров без шаблонной рекурсии.
- `index_sequence` создаёт compile-time индексы для выборки и перестановки элементов.
- `tuple_cat` вместе с type traits позволяет фильтровать кортеж по типам.
- Реализация через шаблонные лямбды требует C++20.
