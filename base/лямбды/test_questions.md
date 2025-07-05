# Тест по лямбда-функциям C++

## Вопрос 1
Что такое функциональный объект в C++?
A) Обычная функция
B) Объект, который можно вызвать с помощью оператора ()
C) Переменная типа std::function
D) Класс с методом operator()

## Вопрос 2
Какой заголовочный файл нужно подключить для работы с std::function?
A) `#include <iostream>`
B) `#include <functional>`
C) `#include <algorithm>`
D) `#include <vector>`

## Вопрос 3
Что означает синтаксис `std::function<int(OrderId)>`?
A) Функция, возвращающая int и принимающая OrderId
B) Функция, возвращающая OrderId и принимающая int
C) Шаблон функции с параметром int
D) Конструктор класса OrderId

## Вопрос 4
Какой код правильно создает лямбда-функцию?
A) `auto lambda = (int x) { return x * 2; };`
B) `auto lambda = [](int x) { return x * 2; };`
C) `auto lambda = {int x} -> { return x * 2; };`
D) `auto lambda = function(int x) { return x * 2; };`

## Вопрос 5
Что обозначают квадратные скобки [] в лямбда-функции?
A) Параметры функции
B) Тело функции
C) Захват переменных
D) Возвращаемый тип

## Вопрос 6
Какой тип захвата использует символ `&` в лямбда-функции?
A) Захват по значению
B) Захват по ссылке
C) Захват по указателю
D) Захват по константной ссылке

## Вопрос 7
Что произойдет при выполнении этого кода?
```cpp
int x = 10;
auto lambda = [&]() { x = 20; };
lambda();
std::cout << x;
```
A) Выведет 10
B) Выведет 20
C) Ошибка компиляции
D) Неопределенное поведение

## Вопрос 8
Какой символ используется для захвата переменных по значению?
A) `&`
B) `=`
C) `*`
D) `%`

## Вопрос 9
Что такое предикат в программировании?
A) Функция, возвращающая void
B) Чистая функция, возвращающая bool
C) Функция с побочными эффектами
D) Функция, принимающая два параметра

## Вопрос 10
Какой алгоритм используется для подсчета элементов по условию?
A) `std::count`
B) `std::count_if`
C) `std::find`
D) `std::find_if`

## Вопрос 11
Что выведет этот код?
```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
int result = std::count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
std::cout << result;
```
A) 2
B) 3
C) 4
D) 5

## Вопрос 12
Какой алгоритм используется для сортировки контейнера?
A) `std::order`
B) `std::sort`
C) `std::arrange`
D) `std::organize`

## Вопрос 13
Что такое компаратор?
A) Функция для сравнения одного элемента
B) Предикат, сравнивающий два элемента и возвращающий bool
C) Функция для подсчета элементов
D) Алгоритм сортировки

## Вопрос 14
Какой компаратор используется по умолчанию в std::sort?
A) `std::greater`
B) `std::less`
C) `std::equal`
D) `std::compare`

## Вопрос 15
Что выведет этот код?
```cpp
std::vector<int> v = {3, 1, 4, 1, 5};
std::sort(v.begin(), v.end(), std::greater<int>());
for(int x : v) std::cout << x << " ";
```
A) 1 1 3 4 5
B) 5 4 3 1 1
C) 3 1 4 1 5
D) 1 3 1 4 5

## Вопрос 16
Какая функция проверяет, отсортирован ли контейнер?
A) `std::check_sorted`
B) `std::is_sorted`
C) `std::verify_sorted`
D) `std::sorted`

## Вопрос 17
Что такое функция обратного вызова (callback)?
A) Функция, которая вызывается автоматически
B) Функция, передаваемая в другую функцию для вызова при определенном событии
C) Функция, которая возвращает другую функцию
D) Рекурсивная функция

## Вопрос 18
Какой код демонстрирует использование callback-функции?
```cpp
// Вариант A
void process(int x, std::function<void(int)> callback) {
    callback(x * 2);
}

// Вариант B
void process(int x) {
    std::cout << x * 2;
}

// Вариант C
int process(int x) {
    return x * 2;
}

// Вариант D
void process(int& x) {
    x *= 2;
}
```
A) Вариант A
B) Вариант B
C) Вариант C
D) Вариант D

## Вопрос 19
Что означает `auto` в параметрах лямбда-функции?
A) Автоматическое определение типа
B) Создание универсальной лямбда-функции
C) Создание шаблонной лямбда-функции
D) Все перечисленное

## Вопрос 20
Какой код создает универсальную лямбда-функцию?
A) `auto lambda = [](int a, int b) { return a + b; };`
B) `auto lambda = [](auto a, auto b) { return a + b; };`
C) `auto lambda = []<typename T>(T a, T b) { return a + b; };`
D) `auto lambda = [](template a, template b) { return a + b; };`

## Вопрос 21
Что произойдет при выполнении этого кода?
```cpp
auto lambda = [](auto a, auto b) { return a + b; };
std::cout << lambda("Hello", "World");
```
A) Выведет "HelloWorld"
B) Ошибка компиляции
C) Выведет адреса строк
D) Неопределенное поведение

## Вопрос 22
Какой алгоритм используется для удаления элементов по условию (C++20)?
A) `std::remove_if`
B) `std::erase_if`
C) `std::delete_if`
D) `std::filter_if`

## Вопрос 23
Что такое фабрика функторов?
A) Класс для создания функций
B) Функция, которая возвращает лямбда-функцию
C) Шаблон для создания функторов
D) Паттерн проектирования

## Вопрос 24
Какой код демонстрирует фабрику функторов?
```cpp
// Вариант A
auto createAdder(int n) {
    return [=](int m) { return n + m; };
}

// Вариант B
auto createAdder(int n) {
    return n + 1;
}

// Вариант C
void createAdder(int n) {
    std::cout << n;
}

// Вариант D
int createAdder(int n, int m) {
    return n + m;
}
```
A) Вариант A
B) Вариант B
C) Вариант C
D) Вариант D

## Вопрос 25
Когда следует использовать захват по ссылке [&]?
A) Когда нужно изменить внешние переменные
B) Когда время жизни переменной больше времени жизни лямбды
C) При создании фабрики функторов
D) Варианты A и B

## Вопрос 26
Что выведет этот код?
```cpp
int counter = 0;
auto increment = [&]() { return ++counter; };
std::cout << increment() << " " << increment() << " " << counter;
```
A) 1 2 2
B) 2 1 2
C) 1 1 0
D) 2 2 2

## Вопрос 27
Какой способ создания std::tuple более эффективен?
A) `std::tuple(a, b)`
B) `std::tie(a, b)`
C) `std::make_tuple(a, b)`
D) Все одинаково эффективны

## Вопрос 28
Что такое лексикографическая сортировка?
A) Сортировка по алфавиту
B) Сортировка по нескольким критериям с приоритетами
C) Сортировка строк
D) Сортировка по длине

## Вопрос 29
Какой код правильно создает шаблонную лямбда-функцию?
A) `auto lambda = []<typename T>(T a, T b) { return a + b; };`
B) `auto lambda = [template T](T a, T b) { return a + b; };`
C) `auto lambda = [](template T a, template T b) { return a + b; };`
D) `auto lambda = []<T>(T a, T b) { return a + b; };`

## Вопрос 30
Что произойдет при выполнении этого кода?
```cpp
std::vector<std::string> words = {"apple", "banana", "cherry"};
std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
    return a.length() < b.length();
});
for(const auto& word : words) std::cout << word << " ";
```
A) apple banana cherry
B) cherry banana apple
C) apple cherry banana
D) banana cherry apple 