Представьте, что вы обнаружили код, который в цикле обходит коллекцию тяжёлых для копирования объектов.

```cpp
class Object {
public:
  explicit Object(size_t count)
    : v(count, 0)
  { }
  size_t getCount() const {
    return v.size();
  }
private:
  std::vector<int> v;
};

std::list<Object> l = {{100}, {1024}, {1024 * 1024}}; 
Упростите написанный цикл с помощью for-range.

auto iter = l.cbegin();
while (iter != l.cend()) {
  std::println(l->getCount());
  ++iter;
} 
```

- Помните, что for-range неявно использует два итератора, полученные с помощью begin() и end() соответственно.

## Задание 2

Вы реализуете алгоритм ротациии элементов и знаете, что для std::vector и других контейнеров, предоставляющих RandomAccessIterator, этот алгоритм уже есть. Bам нужен такой же, только для std::list. Исправьте реализацию функции rotate_prefix так, чтобы она могла работать с ForwardIterator.

```cpp
template <std::random_access_iterator Iterator>
void rotate_prefix(Iterator begin, size_t n) {
  auto end = begin + n + 1;
  auto half = (end - begin) / 2;
  std::rotate(begin, begin + half, end);
} 
```

- Используйте std::distance, чтобы посчитать расстояние между итераторами.
- Используйте std::next, чтобы продвигать итератор на нужное количество элементов.

## Задание 3

Вы разрабатываете алгоритм быстрой сортировки, в котором используется функция выбора опорного элемента, и вас устроит равновероятный выбор элемента из диапазона, заданного итераторами. Дополните определение аргументов шаблона функции pivot так, чтобы использовались только такие типы итераторов, при которых асимптотическая сложность функции будет составлять O(1).

```cpp
template </*ваш код здесь*/>
Iterator pivot
  /*ваш код здесь*/ begin,
  /*ваш код здесь*/ end)
{
  auto d = std::distance(begin, end);
  return begin + rand(0, d);
} 
```
- Вспомните, какие типы итераторов бывают и в чём их особенности.