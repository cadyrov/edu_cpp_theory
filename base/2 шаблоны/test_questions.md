# Тест: Шаблоны C++

## Вопрос 1
Что произойдет при компиляции этого кода?
```cpp
template<typename T>
class MyClass {
public:
    void method() {
        std::cout << "General template" << std::endl;
    }
};

int main() {
    MyClass obj;  // Без указания типа
    obj.method();
}
```

a) Выведет "General template"
b) Ошибка компиляции - не указан тип шаблона
c) Компилятор автоматически выведет тип
d) Будет создан шаблон с типом по умолчанию

## Вопрос 2
В чем разница между `template<typename T>` и `template<class T>`?

a) typename только для встроенных типов, class для пользовательских
b) Никакой разницы, это синонимы
c) class устарел, нужно использовать typename
d) typename быстрее компилируется

## Вопрос 3
Анализируйте код:
```cpp
template<typename T>
class Container {
private:
    std::vector<T> data;
public:
    void add(T item);
};

template<typename T>
void Container<T>::add(T item) {
    data.push_back(item);
}
```
Где должно быть определение метода `add`?

a) В .cpp файле
b) В .h файле или inline в классе
c) В отдельном .tpp файле
d) Неважно где

## Вопрос 4
Что такое инстанцирование (instantiation) шаблона?

a) Создание объекта шаблонного класса
b) Генерация конкретного кода из шаблона компилятором
c) Наследование от шаблонного класса
d) Специализация шаблона

## Вопрос 5
Анализируйте код:
```cpp
template<typename T>
void func(T value) {
    std::cout << value << std::endl;
}

int main() {
    func(42);
    func(3.14);
    func("hello");
}
```
Сколько версий функции `func` создаст компилятор?

a) 1
b) 2  
c) 3
d) 4

## Вопрос 6
Что произойдет с этим кодом?
```cpp
template<typename T>
class Base {
public:
    void baseMethod() {}
};

template<typename T>
class Derived : public Base<T> {
public:
    void someMethod() {
        baseMethod();  // Вызов метода базового класса
    }
};
```

a) Код скомпилируется без ошибок
b) Ошибка - baseMethod не найден
c) Ошибка - неправильное наследование
d) Предупреждение компилятора

## Вопрос 7
Какой синтаксис корректен для специализации шаблона?
```cpp
template<typename T>
class MyClass {};

// Специализация для int
```

a) `template<int> class MyClass<int> {};`
b) `template<> class MyClass<int> {};`
c) `class MyClass<int> {};`
d) `template<typename int> class MyClass {};`

## Вопрос 8
Анализируйте использование SFINAE:
```cpp
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
add(T a, T b) {
    return a + b;
}
```
Для каких типов будет доступна эта функция?

a) Только для int и double
b) Для всех арифметических типов
c) Для всех встроенных типов
d) Для всех типов с operator+

## Вопрос 9
Что такое "двухфазный поиск имен" в шаблонах?

a) Поиск имен сначала в локальной области, потом в глобальной
b) Поиск независимых имен при определении шаблона, зависимых при инстанцировании
c) Поиск в базовом классе, потом в производном
d) Поиск в .h файле, потом в .cpp файле

## Вопрос 10
Анализируйте код:
```cpp
template<typename T>
void process(T&& param) {
    auto copy = std::forward<T>(param);
    // обработка copy
}
```
Что такое `T&&` в контексте шаблонной функции?

a) Rvalue reference
b) Universal reference (forwarding reference)
c) Lvalue reference
d) Pointer reference

## Вопрос 11
Какой код демонстрирует правильную специализацию шаблона?
```cpp
template<typename T>
class Vector {
    T* data;
};

// Специализация для bool
```

a) 
```cpp
template<>
class Vector<bool> {
    std::vector<bool> data;
};
```

b)
```cpp
template<bool>
class Vector<bool> {
    bool* data;
};
```

c)
```cpp
class Vector<bool> {
    bool* data;
};
```

d) Все варианты правильные

## Вопрос 12
Что произойдет при выполнении этого кода?
```cpp
template<int N>
constexpr int factorial() {
    return N <= 1 ? 1 : N * factorial<N-1>();
}

int main() {
    constexpr int result = factorial<5>();
    std::cout << result << std::endl;
}
```

a) Ошибка компиляции
b) Выведет 120, вычисленное во время компиляции
c) Выведет 120, вычисленное во время выполнения
d) Бесконечная рекурсия

## Вопрос 13
Анализируйте вариативный шаблон:
```cpp
template<typename... Args>
void print(Args... args) {
    // Как правильно распечатать все аргументы?
}
```
Какая реализация корректна?

a) `(std::cout << ... << args);`
b) `std::cout << args... << std::endl;`
c) Нужна рекурсивная функция
d) Использовать `sizeof...(args)`

## Вопрос 14
Что неправильно в этом коде?
```cpp
template<typename T>
class MyClass {
public:
    typename T::iterator begin();
};
```

a) Неправильный синтаксис typename
b) Предполагается что T всегда имеет iterator
c) Метод должен быть const
d) Ничего неправильного

## Вопрос 15
Анализируйте частичную специализацию:
```cpp
template<typename T, typename U>
class Pair {};

template<typename T>
class Pair<T, int> {};  // Частичная специализация
```
Это корректно?

a) Да, частичная специализация для классов допустима
b) Нет, частичная специализация не поддерживается
c) Только для шаблонов функций
d) Только с определенными ограничениями

## Вопрос 16
Что выведет этот код?
```cpp
template<typename T>
void func(T value) {
    std::cout << "Template" << std::endl;
}

void func(int value) {
    std::cout << "Specific" << std::endl;
}

int main() {
    func(42);
}
```

a) "Template"
b) "Specific"
c) Ошибка компиляции - неоднозначность
d) Оба сообщения

## Вопрос 17
Анализируйте использование `decltype`:
```cpp
template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}
```
Зачем нужен trailing return type?

a) Для красоты синтаксиса
b) Тип результата зависит от типов параметров
c) Это обязательно для шаблонов
d) Для совместимости с C++98

## Вопрос 18
Что такое SFINAE?

a) Substitution Failure Is An Error
b) Substitution Failure Is Not An Error
c) Simple Function Implementation And Execution
d) Static Function Interface And Environment

## Вопрос 19
Анализируйте код:
```cpp
template<typename T>
struct is_pointer {
    static constexpr bool value = false;
};

template<typename T>
struct is_pointer<T*> {
    static constexpr bool value = true;
};
```
Что это демонстрирует?

a) Полную специализацию
b) Частичную специализацию
c) Type traits
d) Template metaprogramming

## Вопрос 20
Какой код правильно использует `std::enable_if`?

a)
```cpp
template<typename T>
std::enable_if<std::is_integral<T>::value, T>::type
func(T value) { return value; }
```

b)
```cpp
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
func(T value) { return value; }
```

c)
```cpp
template<typename T>
T func(T value, std::enable_if<std::is_integral<T>::value>) { return value; }
```

d) Все варианты правильные

## Вопрос 21
Анализируйте perfect forwarding:
```cpp
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
```
Зачем нужен `std::forward`?

a) Для преобразования в rvalue
b) Для сохранения категории значения
c) Для оптимизации производительности
d) Для предотвращения копирования

## Вопрос 22
Что произойдет с этим кодом?
```cpp
template<typename T>
class Container {
public:
    T data[100];
};

Container<int> c1;
Container<int> c2 = c1;
```

a) Ошибка - нет конструктора копирования
b) Поверхностное копирование массива
c) Глубокое копирование массива поэлементно
d) Ошибка - массивы не копируются

## Вопрос 23
Анализируйте template alias:
```cpp
template<typename T>
using Vector = std::vector<T>;

template<typename K, typename V>
using Map = std::unordered_map<K, V>;
```
В чем преимущество такого подхода?

a) Быстрее компилируется
b) Упрощает синтаксис и повышает читаемость
c) Экономит память
d) Позволяет специализацию

## Вопрос 24
Что неправильно в попытке частичной специализации функции?
```cpp
template<typename T>
void func(T value) {}

template<typename T>
void func<std::vector<T>>(std::vector<T> value) {}  // Ошибка!
```

a) Неправильный синтаксис специализации
b) Частичная специализация функций не поддерживается
c) Нужно использовать class вместо typename
d) Отсутствует template<> для специализации

## Вопрос 25
Анализируйте использование `static_assert`:
```cpp
template<typename T>
void process(T value) {
    static_assert(std::is_copy_constructible<T>::value,
                  "T must be copy constructible");
    // обработка
}
```
Когда произойдет проверка?

a) Во время выполнения
b) Во время компиляции
c) При инстанцировании шаблона
d) При объявлении шаблона

## Вопрос 26
Что выведет этот код?
```cpp
template<typename T>
class Base {
public:
    void print() { std::cout << "Base" << std::endl; }
};

template<>
class Base<int> {
public:
    void print() { std::cout << "Specialized" << std::endl; }
};

int main() {
    Base<double> b1;
    Base<int> b2;
    b1.print();
    b2.print();
}
```

a) "Base" "Base"
b) "Specialized" "Specialized"
c) "Base" "Specialized"
d) Ошибка компиляции

## Вопрос 27
Анализируйте проблему с зависимыми именами:
```cpp
template<typename T>
class Derived : public Base<T> {
public:
    void method() {
        // Как правильно обратиться к методу базового класса?
        Base<T>::baseMethod();
    }
};
```

a) `baseMethod();`
b) `this->baseMethod();`
c) `Base<T>::baseMethod();`
d) b) и c) правильные

## Вопрос 28
Что такое template metaprogramming?

a) Программирование с использованием метаданных
b) Вычисления на этапе компиляции с помощью шаблонов
c) Создание шаблонов во время выполнения
d) Отладка шаблонного кода

## Вопрос 29
Анализируйте fold expression (C++17):
```cpp
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);
}
```
Что произойдет при вызове `sum(1, 2, 3, 4)`?

a) Ошибка компиляции
b) Вернет 10
c) Вернет конкатенацию
d) Нужны дополнительные скобки

## Вопрос 30
Какой тип выведет компилятор?
```cpp
template<typename T>
auto getValue(T&& param) -> decltype(std::forward<T>(param)) {
    return std::forward<T>(param);
}

int x = 5;
auto result = getValue(x);
```

a) `int`
b) `int&`
c) `int&&`
d) `const int&`

## Вопрос 31
Анализируйте использование `typename`:
```cpp
template<typename T>
void func() {
    T::iterator it;  // Ошибка!
    // Как исправить?
}
```

a) `auto it = T::iterator{};`
b) `typename T::iterator it;`
c) `T::iterator* it;`
d) Исправить нельзя

## Вопрос 32
Что демонстрирует этот код?
```cpp
template<bool Condition, typename T = void>
struct enable_if {};

template<typename T>
struct enable_if<true, T> {
    using type = T;
};
```

a) Template specialization
b) SFINAE implementation
c) Type traits
d) Все перечисленное

## Вопрос 33
Анализируйте variadic templates:
```cpp
template<typename T>
void print(T&& value) {
    std::cout << value << std::endl;
}

template<typename T, typename... Args>
void print(T&& first, Args&&... args) {
    std::cout << first << " ";
    print(args...);
}
```
Что произойдет при вызове `print(1, 2, 3)`?

a) Выведет "1 2 3"
b) Выведет "1 2 3" каждое на новой строке
c) Ошибка компиляции
d) Бесконечная рекурсия

## Вопрос 34
Какие ограничения есть у шаблонных параметров?

a) Можно использовать только встроенные типы
b) Можно использовать типы, значения и шаблоны
c) Только классы и структуры
d) Только POD типы

## Вопрос 35
Анализируйте template template parameter:
```cpp
template<template<typename> class Container, typename T>
class Wrapper {
    Container<T> data;
};
```
Это пример чего?

a) Частичной специализации
b) Template template parameter
c) Variadic template
d) Type alias

## Вопрос 36
Что произойдет при компиляции?
```cpp
template<typename T>
void func(T value) {
    typename T::nonexistent_type x;  // T может не иметь этого типа
}

int main() {
    // func(42);  // Если раскомментировать
    return 0;
}
```

a) Ошибка компиляции сразу
b) Ошибка только при инстанцировании
c) Код скомпилируется без ошибок
d) Предупреждение компилятора

## Вопрос 37
Анализируйте template argument deduction:
```cpp
template<typename T>
void func(const T& value) {}

func("hello");  // Какой тип выведет компилятор для T?
```

a) `std::string`
b) `const char*`
c) `char[6]`
d) `const char[6]`

## Вопрос 38
Что такое ADL (Argument Dependent Lookup) в контексте шаблонов?

a) Automatic Template Deduction
b) Поиск функций в namespace аргументов
c) Advanced Template Logic
d) Automatic Type Deduction

## Вопрос 39
Анализируйте проблему с экспортом шаблонов:
```cpp
// file.h
template<typename T>
class MyClass {
public:
    void method();
};

// file.cpp
template<typename T>
void MyClass<T>::method() {
    // реализация
}
```
В чем проблема?

a) Неправильный синтаксис
b) Определения шаблонов должны быть в заголовочных файлах
c) Нужна явная инстанциация
d) Нет проблем

## Вопрос 40
Какой из подходов предпочтительнее для ограничения типов шаблона?

a) Множественные специализации для каждого типа
b) SFINAE с `std::enable_if`
c) Проверка типов в runtime
d) Использование макросов 