Потренируйтесь в написании constexpr-функции-хелпера для обработки строк на этапе компиляции. 

Скопируйте код ниже себе и напишите реализацию функции getMaxSize, которая находит самую длинную строку из переданных и возвращает её размер.
```cpp

#include <string>

// Здесь реализация функции getMaxSize

int main() {
  assert(getMaxSize({"hello", "s", "ab", "hhh"}) == 5);
  static_assert(getMaxSize({"hello", "s", "ab", "world!"}) == 6);
  return 0;
} 
```

- constexpr выполняется и во время компиляции, и во время работы программы.
- Все методы std::string являются constexpr.
- В constexpr можно использовать алгоритмы, например std::sort.

## Задание 2

Представьте, что вам стало интересно узнать, используется ли механизм оптимизации коротких строк (SSO) для некоторой строки s. 

Скопируйте код ниже себе и напишите функцию bool isSSO(const std::string &s), которая возвращает true, если ваша реализация std::string применяет её, иначе false.

```cpp

#include <string>
#include <print>

[[nodiscard]] bool isSSO(const std::string &s) {
    // Ваш код
}

int main() {
    const std::string shortString = "sso";
    const std::string longString(100, 'x');

    std::println("isSSO(short) = {}", isSSO(shortString));
    std::println("isSSO(long) = {}", isSSO(longString));

    return 0;
} 
```

- Используйте std::string::data() для получения указателя на сами данные.
- Подумайте, как можно определить диапазон адресов (начало и конец), в котором лежит объект std::string, и как это можно применить к решению задачи.