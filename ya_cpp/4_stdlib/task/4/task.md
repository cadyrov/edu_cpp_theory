Представьте, что вы разработчик встраиваемых систем. В вашей команде ценят оптимизации, которые позволяют уменьшить время работы алгоритмов. Вам поручили написать функции-хелперы, и вы решили применить в них выполнения кода в ходе компиляции.

Скопируйте код ниже к себе и реализуйте функцию, которая вычисляет количество уникальных элементов в контейнере в ходе компиляции.

```cpp
#include <algorithm>
#include <vector>
#include <iterator>

template <class Container>
constexpr size_t findUniqueCount(const Container& items) {
    // ваш код здесь
}

int main() {
    static_assert(findUniqueCount(std::vector<std::string>{"a", "c", "c", "z", "z", "a"}) == 3);
    static_assert(findUniqueCount(std::vector{1, 2, 100, 11, 22, 22, 2}) == 5);
    return 0;
} 
```

- Для вычисления типа элемента контейнера используйте std::iter_value_t.