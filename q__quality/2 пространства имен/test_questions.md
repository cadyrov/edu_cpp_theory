# Тест по теме "Пространства имен" (40 вопросов)

## Вопрос 1
Что произойдет при компиляции следующего кода?
```cpp
namespace A {
    int x = 5;
}
namespace A {
    int y = 10;
}
int main() {
    return A::x + A::y;
}
```
a) Ошибка компиляции: пространство имен A определено дважды
b) Программа скомпилируется и вернет 15
c) Ошибка компиляции: переменные x и y недоступны
d) Неопределенное поведение

## Вопрос 2
Какой будет результат выполнения данного кода?
```cpp
#include <iostream>
namespace test {
    int value = 42;
}
using namespace test;
int main() {
    int value = 100;
    std::cout << value << " " << ::test::value;
    return 0;
}
```
a) 42 42
b) 100 42
c) 100 100
d) Ошибка компиляции

## Вопрос 3
Что неправильно в следующем коде?
```cpp
// header.h
#include <vector>
using namespace std;

class MyClass {
    vector<int> data;
};
```
a) Нет ошибок
b) using namespace std в заголовочном файле
c) Неправильное использование vector
d) Отсутствует include guard

## Вопрос 4
Как правильно определить функцию вне пространства имен?
```cpp
namespace math {
    double calculate(double x);
}
```
a) `double math::calculate(double x) { return x * 2; }`
b) `double calculate(double x) { return x * 2; }`
c) `math::double calculate(double x) { return x * 2; }`
d) `namespace math { double calculate(double x) { return x * 2; } }`

## Вопрос 5
Что выведет следующий код?
```cpp
#include <iostream>
namespace outer {
    namespace inner {
        int value = 10;
    }
    int value = 20;
}
int main() {
    using namespace outer;
    std::cout << value << " " << inner::value;
    return 0;
}
```
a) 10 10
b) 20 10
c) 10 20
d) Ошибка компиляции

## Вопрос 6
Какое квалифицированное имя у функции `func`?
```cpp
namespace A {
    namespace B {
        namespace C {
            void func();
        }
    }
}
```
a) A::B::C::func
b) A.B.C.func
c) A/B/C/func
d) A->B->C->func

## Вопрос 7
Что произойдет при компиляции?
```cpp
namespace first {
    class Node {};
}
namespace second {
    class Node {};
}
using namespace first;
using namespace second;
int main() {
    Node n; // Ошибка здесь
    return 0;
}
```
a) Программа скомпилируется успешно
b) Ошибка: reference to 'Node' is ambiguous
c) Будет использована first::Node
d) Будет использована second::Node

## Вопрос 8
Что делает следующая конструкция?
```cpp
namespace alias = very::long::namespace::name;
```
a) Создает новое пространство имен
b) Создает псевдоним для пространства имен
c) Переименовывает пространство имен
d) Удаляет пространство имен

## Вопрос 9
Какой оператор используется для доступа к глобальному пространству имен?
```cpp
int global_var = 5;
namespace test {
    int global_var = 10;
    void func() {
        // как обратиться к ::global_var?
    }
}
```
a) `global::`
b) `::`
c) `global_ns::`
d) `std::`

## Вопрос 10
Что неверно в использовании anonymous namespace?
```cpp
namespace {
    void helperFunction() {}
    int internalData = 42;
}
void func() {
    helperFunction(); // правильно ли это?
}
```
a) Нельзя использовать anonymous namespace
b) Нет ошибок
c) helperFunction недоступна
d) internalData должна быть константой

## Вопрос 11
Что выведет данный код?
```cpp
#include <iostream>
namespace test {
    struct Point { int x, y; };
    void print(Point p) { std::cout << "test::print"; }
}
int main() {
    test::Point p{1, 2};
    print(p); // ADL сработает?
    return 0;
}
```
a) Ошибка компиляции: print не найдена
b) test::print
c) Неопределенное поведение
d) Выведет адрес функции

## Вопрос 12
Какая разница между using-декларацией и using-директивой?
```cpp
// Вариант A
using std::vector;

// Вариант B  
using namespace std;
```
a) Никакой разницы
b) A импортирует только vector, B - все имена std
c) A создает псевдоним, B - импортирует
d) A работает только в функциях, B - глобально

## Вопрос 13
Что произойдет с данным кодом?
```cpp
namespace std {
    void myFunction() { /* что-то */ }
}
```
a) Программа скомпилируется нормально
b) Предупреждение компилятора
c) Неопределенное поведение (нарушение стандарта)
d) Ошибка компиляции

## Вопрос 14
В каком случае стоит использовать пространства имен?
a) Всегда, для любого кода
b) Только в больших проектах и библиотеках
c) Никогда, они усложняют код
d) Только для стандартной библиотеки

## Вопрос 15
Что выведет следующий код?
```cpp
#include <iostream>
namespace A {
    void func() { std::cout << "A"; }
}
namespace B {
    void func() { std::cout << "B"; }
}
using A::func;
using B::func; // что здесь происходит?
int main() {
    func();
    return 0;
}
```
a) A
b) B
c) AB
d) Ошибка компиляции

## Вопрос 16
Как правильно объявить класс в пространстве имен в заголовочном файле?
a) `class namespace::MyClass { };`
b) `namespace::class MyClass { };`
c) `namespace my { class MyClass { }; }`
d) `using namespace my; class MyClass { };`

## Вопрос 17
Что делает inline namespace?
```cpp
namespace mylib {
    inline namespace v2 {
        class NewAPI {};
    }
    namespace v1 {
        class OldAPI {};
    }
}
```
a) Ускоряет компиляцию
b) Делает v2 пространством по умолчанию для mylib
c) Встраивает код в место вызова
d) Создает синоним пространства имен

## Вопрос 18
Какая проблема в следующем коде?
```cpp
#include <cmath>
void sortDocuments() {
    double diff = 0.1;
    if (abs(diff) < 1e-6) { // проблема здесь
        // ...
    }
}
```
a) Нет проблем
b) abs может быть неправильной версией (int вместо double)
c) diff не может быть 0.1
d) Неправильное условие сравнения

## Вопрос 19
Что произойдет при компиляции?
```cpp
namespace outer {
    int x = 1;
    namespace inner {
        int x = 2;
        void func() {
            std::cout << x;      // какой x?
            std::cout << outer::x; // а здесь?
        }
    }
}
```
a) Ошибка: конфликт имен
b) Выведет: 2 1
c) Выведет: 1 1
d) Выведет: 2 2

## Вопрос 20
Где уместно использовать using namespace std?
a) В заголовочных файлах
b) В cpp-файлах
c) В inline функциях
d) Никогда

## Вопрос 21
Что выведет данный код?
```cpp
#include <iostream>
namespace test {
    class Data {};
    void process(Data d) { std::cout << "processed"; }
}
namespace other {
    void process(int x) { std::cout << "int"; }
}
using namespace other;
int main() {
    test::Data d;
    process(d); // ADL
    return 0;
}
```
a) int
b) processed
c) Ошибка компиляции
d) Неопределенное поведение

## Вопрос 22
Какой уровень вложенности пространств имен считается максимально разумным?
a) 1
b) 2-3
c) 5-6
d) Без ограничений

## Вопрос 23
Что означает квалификация ::?
```cpp
int global_x = 10;
namespace test {
    int global_x = 20;
    void func() {
        std::cout << ::global_x; // что это?
    }
}
```
a) Доступ к test::global_x
b) Доступ к глобальному global_x
c) Ошибка синтаксиса
d) Доступ к std::global_x

## Вопрос 24
Что неправильно в структуре namespace?
```cpp
namespace graphics {
    class Window {};
    class Button {};
}
namespace math {
    class Vector {};
}
namespace graphics { // можно ли так?
    class Menu {};
}
```
a) Нельзя определять namespace graphics дважды
b) Нет ошибок
c) math должен быть внутри graphics
d) Menu должен быть в отдельном файле

## Вопрос 25
Что произойдет при попытке компиляции?
```cpp
namespace A {
    namespace B {
        int value = 42;
    }
}
using namespace A::B; // правильно ли это?
int main() {
    std::cout << value;
    return 0;
}
```
a) Ошибка: неправильный синтаксис using
b) Выведет 42
c) Ошибка: value не найден
d) Предупреждение компилятора

## Вопрос 26
Какая лучшая практика для naming namespace?
a) Очень длинные описательные имена
b) Короткие аббревиатуры
c) Краткие, но понятные имена
d) Имена на национальном языке

## Вопрос 27
Что выведет код?
```cpp
#include <iostream>
namespace {
    int secret = 100;
}
int main() {
    std::cout << secret;
    return 0;
}
```
a) Ошибка: secret недоступен
b) 100
c) Предупреждение компилятора
d) Неопределенное поведение

## Вопрос 28
Правильно ли следующее определение метода?
```cpp
namespace math {
    class Calculator {
        int add(int a, int b);
    };
}
int math::Calculator::add(int a, int b) {
    return a + b;
}
```
a) Да, правильно
b) Нет, должно быть внутри namespace
c) Нет, неправильная квалификация
d) Нет, нужен inline

## Вопрос 29
Что делает следующая конструкция?
```cpp
namespace parent {
    using namespace child;
}
```
a) Создает вложенное пространство
b) Импортирует все имена child в parent
c) Создает псевдоним
d) Переименовывает child в parent

## Вопрос 30
Когда возникает конфликт имен при поиске?
```cpp
namespace A { void func(); }
namespace B { void func(); }
using namespace A;
using namespace B;
// func(); - конфликт?
```
a) Всегда при использовании using namespace
b) Только при вызове func()
c) Только при определении func()
d) Никогда

## Вопрос 31
Что выведет данный код?
```cpp
#include <iostream>
namespace outer {
    int x = 1;
    namespace inner {
        using outer::x;
        void test() { std::cout << x; }
    }
}
int main() {
    outer::inner::test();
    return 0;
}
```
a) Ошибка компиляции
b) 1
c) 0
d) Неопределенное поведение

## Вопрос 32
Какая проблема с глубоко вложенными namespace?
```cpp
namespace company {
namespace project {
namespace module {
namespace submodule {
    class Worker {};
}}}}
```
a) Нет проблем
b) Слишком длинные квалифицированные имена
c) Ошибка компиляции
d) Медленная компиляция

## Вопрос 33
Что произойдет при выполнении?
```cpp
#include <iostream>
namespace test {
    void func() { std::cout << "namespace"; }
}
void func() { std::cout << "global"; }
int main() {
    func();      // какая func?
    test::func(); // а здесь?
    return 0;
}
```
a) namespace namespace
b) global namespace
c) Ошибка компиляции
d) global global

## Вопрос 34
Правильно ли использование namespace для одного класса?
```cpp
namespace single_class {
    class OnlyOne {
        // единственный класс в namespace
    };
}
```
a) Да, это хорошая практика
b) Нет, namespace не нужен для одного класса
c) Да, но только для больших классов
d) Зависит от размера класса

## Вопрос 35
Что означает следующая ошибка компилятора?
"error: reference to 'Vector' is ambiguous"
a) Vector не определен
b) Несколько определений Vector в разных namespace
c) Vector определен неправильно
d) Отсутствует include

## Вопрос 36
Как правильно использовать namespace detail?
```cpp
namespace mylib {
    class PublicAPI {};
    
    namespace detail {
        class InternalHelper {}; // правильно ли это?
    }
}
```
a) Нет, detail должен быть отдельным namespace
b) Да, для внутренних деталей реализации
c) Нет, detail зарезервированное слово
d) Да, но только для функций

## Вопрос 37
Что выведет код при использовании using-декларации?
```cpp
#include <iostream>
namespace A { int x = 10; }
namespace B { int x = 20; }
using A::x;
int main() {
    std::cout << x;
    return 0;
}
```
a) 10
b) 20
c) Ошибка компиляции
d) 30

## Вопрос 38
Какая разница между этими двумя подходами?
```cpp
// Подход 1
namespace math::geometry { class Point {}; }

// Подход 2  
namespace math {
    namespace geometry {
        class Point {};
    }
}
```
a) Первый подход невалиден
b) Нет разницы (начиная с C++17)
c) Первый создает вложенность, второй - нет
d) Второй подход невалиден

## Вопрос 39
Что происходит при поиске имени в namespace?
```cpp
namespace outer {
    int value = 1;
    namespace inner {
        void func() {
            std::cout << value; // какой поиск?
        }
    }
}
```
a) Поиск только в inner
b) Поиск в inner, затем в outer
c) Поиск только в outer
d) Поиск во всех namespace

## Вопрос 40
Какая лучшая практика для библиотек с namespace?
```cpp
// Вариант A
namespace mylib_v1 { /* API */ }

// Вариант B
namespace mylib {
    inline namespace v1 { /* API */ }
}
```
a) Вариант A лучше
b) Вариант B лучше для версионирования
c) Оба варианта одинаковы
d) Лучше без namespace 