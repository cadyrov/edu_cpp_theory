# 8. Вспомогательные средства ranges

## Суть

Ranges защищают от висячих итераторов и позволяют материализовать ленивый диапазон в контейнер.

Основные средства:

- `std::ranges::dangling` — безопасная замена невалидного итератора;
- `std::ranges::borrowed_range` — диапазон, итераторы которого не зависят от жизни его объекта;
- `std::ranges::to` — преобразование диапазона в контейнер.

## `borrowed_iterator_t` и `dangling`

Многие ranges-алгоритмы возвращают тип `std::ranges::borrowed_iterator_t<R>`:

```cpp
template <std::ranges::range R>
using borrowed_iterator_t = std::conditional_t<
    std::ranges::borrowed_range<R>,
    std::ranges::iterator_t<R>,
    std::ranges::dangling
>;
```

Для обычного именованного контейнера вернётся итератор:

```cpp
std::vector<int> values{1, 2, 3};
auto it = std::ranges::find(values, 2);

std::println("{}", *it); // 2
```

Для временного владеющего контейнера вернётся `dangling`:

```cpp
auto result = std::ranges::find(std::vector{1, 2, 3}, 2);
// *result; // ошибка компиляции
```

Временный вектор уже уничтожен, поэтому возвращать его итератор было бы опасно. Выбор между итератором и `dangling` происходит на этапе компиляции.

## `borrowed_range`

Диапазон удовлетворяет `borrowed_range`, если:

- он передан как lvalue-ссылка; или
- для его типа включён `std::ranges::enable_borrowed_range`.

```cpp
std::vector<int> values{1, 2, 3};

static_assert(
    std::ranges::borrowed_range<decltype((values))>
);
```

Некоторые невладеющие или самодостаточные диапазоны остаются безопасными даже как временные объекты:

```cpp
using namespace std::literals;

auto letter = std::ranges::find("hello"sv, 'e');
auto number = std::ranges::find(std::views::iota(1, 5), 3);

std::println("{} {}", *letter, *number);
```

Примеры borrowed-range-типов:

- `std::string_view`;
- `std::span`;
- `std::ranges::subrange`;
- `std::ranges::ref_view`;
- `std::ranges::iota_view`.

## `std::ranges::to`

`std::ranges::to` материализует элементы диапазона в контейнер. Доступен с C++23.

```cpp
auto squares = std::views::iota(1, 5)
             | std::views::transform([](int x) {
                   return x * x;
               })
             | std::ranges::to<std::vector>();

// vector: 1, 4, 9, 16
```

Он также удобен для вложенных диапазонов:

```cpp
std::string text = "C++ ranges";

auto words = text
    | std::views::split(' ')
    | std::views::transform([](auto&& part) {
          return std::ranges::to<std::string>(part);
      })
    | std::ranges::to<std::vector>();
```

## Подводные камни

### 1. `dangling` не продлевает жизнь объекта

Он лишь не позволяет случайно использовать заведомо невалидный итератор.

### 2. Временный view не всегда безопасен

Сам факт, что тип является `view`, не делает его `borrowed_range`. Всё зависит от конкретного типа и базового диапазона.

### 3. `borrowed_range` не гарантирует жизнь данных вообще

Например, `string_view` безопасен только пока существует строка, на которую он ссылается. Концепт гарантирует независимость итераторов от жизни самого объекта view, а не исходного хранилища.

### 4. `ranges::to` выполняет вычисления

Материализация обходит весь диапазон, выделяет память и сохраняет элементы. Бесконечный диапазон сначала нужно ограничить.

### 5. `ranges::to` требует C++23

В C++20 контейнер заполняют через конструктор, `std::ranges::copy` или другой алгоритм.

## Саммари

- Алгоритм возвращает `dangling`, если итератор временного диапазона стал бы невалидным.
- `borrowed_range` описывает диапазоны с итераторами, независимыми от жизни объекта диапазона.
- Именованный диапазон, переданный как lvalue, даёт валидный итератор.
- Не каждый view является borrowed range.
- `ranges::to` материализует ленивый диапазон в контейнер.
