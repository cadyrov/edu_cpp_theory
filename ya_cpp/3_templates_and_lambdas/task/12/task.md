Представьте, что в качестве нетипового параметра шаблона вам нужно использовать строку, но ни один из очевидных способов здесь не работает:

```cpp
template <auto T>
struct FormatString {};

FormatString<"{} {}"> fs0;  // Ошибка компиляции: string literals can never be used in this context

using namespace std::string_literals;
FormatString<"{} {}"s>
    fs1;  // Ошибка компиляции:  type 'basic_string<char>' of non-type template parameter is not a structural type 
```
Коллега подсказал решение: использовать в качестве нетипового параметра шаблона FormatString структуру с массивом символов — и набросал такой черновик:

```cpp
#include <algorithm>
#include <print>

template <typename CharT, std::size_t N>
struct fixed_string;

template <fixed_string Str>
struct FormatString {
    void test_print() { std::println(Str.data, "Hello, ", "world!"); }
};

int main() {
    FormatString<"{} {}"> fs;
    fs.test_print();
}
```
Вам осталось совсем немного, чтобы доделать шаблон `fixed_string`. Скопируйте код ниже к себе и напишите конструктор, принимающий массив символов и копирующий его в `data`: 

```cpp
template <typename CharT, std::size_t N>
struct fixed_string {
    CharT data[N]{};
    /* Реализуйте здесь конструктор, принимающий массив символов */
}; 
```
- Конструктор должен быть constexpr, ведь объект используется как параметр шаблона.
- Используйте параметры шаблона, чтобы задать тип аргумента конструктора.
- Скопируйте символы из аргумента в data.
- Для копирования можете использовать std::copy_n.