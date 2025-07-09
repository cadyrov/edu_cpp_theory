# Тест по семантике перемещений C++

## Вопрос 1
Что произойдет при выполнении следующего кода?
```cpp
std::vector<std::string> vec;
std::string str = "Hello";
vec.push_back(std::move(str));
std::cout << str << std::endl;
```
A) Выведет "Hello"
B) Выведет пустую строку
C) Ошибка компиляции
D) Неопределенное поведение

## Вопрос 2
Какой из следующих конструкторов перемещения корректен?
```cpp
A) MyClass(MyClass&& other) : data_(other.data_) {}
B) MyClass(MyClass&& other) noexcept : data_(std::move(other.data_)) {}
C) MyClass(const MyClass&& other) : data_(std::move(other.data_)) {}
D) MyClass(MyClass& other) : data_(std::move(other.data_)) {}
```

## Вопрос 3
Что такое copy elision?
A) Техника копирования объектов
B) Оптимизация компилятора, избегающая ненужных копирований
C) Механизм перемещения объектов
D) Способ удаления объектов из памяти

## Вопрос 4
Какой результат выполнения кода?
```cpp
class Test {
public:
    Test() { std::cout << "Ctor "; }
    Test(const Test&) { std::cout << "Copy "; }
    Test(Test&&) { std::cout << "Move "; }
    ~Test() { std::cout << "Dtor "; }
};

Test CreateTest() {
    return Test();
}

int main() {
    Test t = CreateTest();
    return 0;
}
```
A) Ctor Copy Dtor Dtor
B) Ctor Move Dtor Dtor
C) Ctor Dtor
D) Ctor Move Copy Dtor Dtor Dtor

## Вопрос 5
Что делает функция std::exchange?
A) Меняет местами два объекта
B) Присваивает новое значение переменной и возвращает старое
C) Перемещает объект в другое место памяти
D) Копирует объект

## Вопрос 6
Когда следует использовать noexcept в конструкторе перемещения?
A) Никогда
B) Всегда
C) Когда операция гарантированно не бросает исключения
D) Только для примитивных типов

## Вопрос 7
Что произойдет при выполнении?
```cpp
std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
std::unique_ptr<int> ptr2 = ptr1;
```
A) ptr2 будет содержать копию значения
B) ptr2 будет указывать на тот же объект, что и ptr1
C) Ошибка компиляции
D) Неопределенное поведение

## Вопрос 8
Какая из перегрузок будет вызвана?
```cpp
void func(const std::string& s) { std::cout << "lvalue"; }
void func(std::string&& s) { std::cout << "rvalue"; }

std::string str = "test";
func(std::move(str));
```
A) lvalue
B) rvalue
C) Обе
D) Ошибка компиляции

## Вопрос 9
Что такое NRVO?
A) Named Return Value Optimization
B) New Return Value Operation
C) Non-Recursive Virtual Override
D) Null Reference Value Object

## Вопрос 10
Какой код более эффективен для перемещаемых типов?
```cpp
A) void func(const std::vector<int>& v) { data_ = v; }
B) void func(std::vector<int> v) { data_ = std::move(v); }
C) void func(std::vector<int>&& v) { data_ = std::move(v); }
D) void func(std::vector<int>* v) { data_ = *v; }
```

## Вопрос 11
Что выведет следующий код?
```cpp
class Resource {
    std::string name_;
public:
    Resource(std::string n) : name_(std::move(n)) {}
    Resource(Resource&& other) noexcept 
        : name_(std::exchange(other.name_, "moved")) {}
    const std::string& GetName() const { return name_; }
};

Resource r1("original");
Resource r2(std::move(r1));
std::cout << r1.GetName() << " " << r2.GetName();
```
A) original original
B) moved original
C) original moved
D) moved moved

## Вопрос 12
Какой из методов std::vector поддерживает move-семантику?
A) at()
B) operator[]
C) push_back()
D) size()

## Вопрос 13
Что произойдет при компиляции?
```cpp
class NonMovable {
public:
    NonMovable(const NonMovable&) = delete;
    NonMovable& operator=(const NonMovable&) = delete;
    NonMovable(NonMovable&&) = delete;
    NonMovable& operator=(NonMovable&&) = delete;
};

NonMovable CreateNonMovable() {
    return NonMovable();
}
```
A) Скомпилируется успешно
B) Ошибка компиляции из-за отсутствия конструктора копирования
C) Ошибка компиляции из-за отсутствия конструктора перемещения
D) Ошибка компиляции из-за отсутствия конструктора по умолчанию

## Вопрос 14
Какая сложность перемещения std::array<int, 1000>?
A) O(1)
B) O(log n)
C) O(n)
D) O(n²)

## Вопрос 15
Что делает std::make_move_iterator?
A) Создает итератор, который перемещает элементы при разыменовании
B) Перемещает итератор на следующую позицию
C) Создает копию итератора
D) Удаляет элемент, на который указывает итератор

## Вопрос 16
Какой код демонстрирует правильное использование move-семантики?
```cpp
A) return std::move(local_variable);
B) std::vector<int> v = std::move(GetVector());
C) container.push_back(std::move(temporary_object));
D) auto result = std::move(function_call());
```

## Вопрос 17
Что произойдет при выполнении?
```cpp
std::string s1 = "Hello";
std::string s2 = "World";
std::string s3 = std::move(s1) + std::move(s2);
std::cout << s1.size() << " " << s2.size() << " " << s3.size();
```
A) 5 5 10
B) 0 0 10
C) 0 5 10
D) Результат не определен

## Вопрос 18
Когда copy elision НЕ работает?
A) При возврате локальной переменной
B) При возврате временного объекта
C) При возврате поля объекта
D) При инициализации объекта временным значением

## Вопрос 19
Что такое rvalue-ссылка?
A) Ссылка на правую часть выражения
B) Ссылка на временный объект или объект, который можно переместить
C) Ссылка на константный объект
D) Ссылка на ссылку

## Вопрос 20
Какой из операторов присваивания корректен?
```cpp
A) MyClass& operator=(MyClass&& other) {
     data_ = other.data_;
     return *this;
   }
B) MyClass& operator=(MyClass&& other) noexcept {
     if (this != &other) {
         data_ = std::move(other.data_);
     }
     return *this;
   }
C) MyClass& operator=(const MyClass&& other) {
     data_ = std::move(other.data_);
     return *this;
   }
D) MyClass operator=(MyClass&& other) {
     data_ = std::move(other.data_);
     return *this;
   }
```

## Вопрос 21
Что выведет код?
```cpp
class Counter {
    static int count_;
public:
    Counter() { ++count_; }
    Counter(const Counter&) { ++count_; }
    Counter(Counter&&) { ++count_; }
    ~Counter() { --count_; }
    static int GetCount() { return count_; }
};
int Counter::count_ = 0;

void func() {
    Counter c1;
    Counter c2 = std::move(c1);
    std::cout << Counter::GetCount() << " ";
}

int main() {
    func();
    std::cout << Counter::GetCount();
    return 0;
}
```
A) 2 0
B) 1 0
C) 2 2
D) 1 1

## Вопрос 22
Какой способ передачи параметра наиболее эффективен для std::string?
A) void func(std::string s)
B) void func(const std::string& s)
C) void func(std::string&& s)
D) Зависит от контекста использования

## Вопрос 23
Что произойдет при выполнении?
```cpp
std::vector<int> v1 = {1, 2, 3};
std::vector<int> v2 = std::move(v1);
v1.push_back(4);
std::cout << v1.size() << " " << v2.size();
```
A) 4 3
B) 1 3
C) 0 3
D) Неопределенное поведение

## Вопрос 24
Какая из функций может воспользоваться RVO?
```cpp
A) std::string func() { std::string s = "test"; return std::move(s); }
B) std::string func() { std::string s = "test"; return s; }
C) std::string func() { return std::string("test"); }
D) B и C
```

## Вопрос 25
Что делает std::forward?
A) Перемещает объект вперед в памяти
B) Идеально передает аргумент с сохранением его категории значения
C) Создает копию объекта
D) Удаляет объект

## Вопрос 26
Какой код приведет к ошибке компиляции?
```cpp
A) std::unique_ptr<int> ptr = std::make_unique<int>(42);
   std::unique_ptr<int> ptr2 = std::move(ptr);
B) std::unique_ptr<int> ptr = std::make_unique<int>(42);
   std::unique_ptr<int> ptr2 = ptr;
C) std::unique_ptr<int> ptr = std::make_unique<int>(42);
   std::unique_ptr<int> ptr2(std::move(ptr));
D) std::unique_ptr<int> ptr = std::make_unique<int>(42);
   auto ptr2 = std::move(ptr);
```

## Вопрос 27
Что выведет код?
```cpp
class Test {
public:
    Test() = default;
    Test(const Test&) { std::cout << "Copy "; }
    Test(Test&&) { std::cout << "Move "; }
};

Test CreateTest() {
    Test t;
    return t;  // NRVO
}

int main() {
    Test t = CreateTest();
    return 0;
}
```
A) Copy
B) Move
C) Ничего не выведет
D) Copy Move

## Вопрос 28
Какой из контейнеров имеет наименее эффективное перемещение?
A) std::vector
B) std::list
C) std::array
D) std::deque

## Вопрос 29
Что произойдет при выполнении?
```cpp
std::vector<std::string> vec = {"a", "b", "c"};
std::vector<std::string> moved_vec(
    std::make_move_iterator(vec.begin()),
    std::make_move_iterator(vec.end())
);
std::cout << vec[0] << " " << moved_vec[0];
```
A) a a
B) (пусто) a
C) a (пусто)
D) Неопределенное поведение

## Вопрос 30
Какой из методов НЕ поддерживает move-семантику?
A) std::vector::push_back
B) std::vector::emplace_back
C) std::vector::insert
D) std::vector::at

## Вопрос 31
Что выведет код?
```cpp
class Resource {
    std::unique_ptr<int> data_;
public:
    Resource() : data_(std::make_unique<int>(42)) {}
    Resource(Resource&& other) noexcept = default;
    Resource& operator=(Resource&& other) noexcept = default;
    
    int GetValue() const { return data_ ? *data_ : -1; }
};

Resource r1;
Resource r2 = std::move(r1);
std::cout << r1.GetValue() << " " << r2.GetValue();
```
A) 42 42
B) -1 42
C) 42 -1
D) -1 -1

## Вопрос 32
Какой из способов инициализации наиболее эффективен?
```cpp
A) std::vector<std::string> vec; vec.push_back(std::string("test"));
B) std::vector<std::string> vec; vec.emplace_back("test");
C) std::vector<std::string> vec; vec.emplace_back(std::string("test"));
D) std::vector<std::string> vec{"test"};
```

## Вопрос 33
Что произойдет при выполнении?
```cpp
struct NonCopyable {
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) = default;
};

NonCopyable CreateObject() {
    return NonCopyable();
}

int main() {
    NonCopyable obj = CreateObject();
    return 0;
}
```
A) Ошибка компиляции
B) Успешная компиляция и выполнение
C) Ошибка выполнения
D) Неопределенное поведение

## Вопрос 34
Какой оператор следует использовать для проверки возможности перемещения в C++17?
A) std::is_moveable_v
B) std::is_move_constructible_v
C) std::can_move_v
D) std::has_move_constructor_v

## Вопрос 35
Что выведет код?
```cpp
std::string CreateString() {
    std::string local = "Hello";
    return std::move(local);  // Плохая практика
}

std::string CreateString2() {
    std::string local = "World";
    return local;  // Хорошая практика
}

int main() {
    auto s1 = CreateString();
    auto s2 = CreateString2();
    std::cout << s1 << " " << s2;
    return 0;
}
```
A) Hello World
B) (пусто) World
C) Hello (пусто)
D) (пусто) (пусто)

## Вопрос 36
Какой из следующих типов НЕ поддерживает move-семантику по умолчанию?
A) std::string
B) std::vector
C) std::ostream
D) std::unique_ptr

## Вопрос 37
Что произойдет при выполнении?
```cpp
class Test {
public:
    Test() { std::cout << "1"; }
    Test(const Test&) { std::cout << "2"; }
    Test(Test&&) { std::cout << "3"; }
    ~Test() { std::cout << "4"; }
};

void func(Test t) {
    // пустая функция
}

int main() {
    Test t;
    func(std::move(t));
    return 0;
}
```
A) 1344
B) 1234
C) 1324
D) 1244

## Вопрос 38
Какой код демонстрирует правильное использование std::exchange?
```cpp
A) MyClass(MyClass&& other) : data_(std::exchange(other.data_, nullptr)) {}
B) MyClass(MyClass&& other) : data_(std::exchange(nullptr, other.data_)) {}
C) MyClass(MyClass&& other) : data_(std::exchange(other.data_, data_)) {}
D) MyClass(MyClass&& other) : data_(std::exchange(data_, other.data_)) {}
```

## Вопрос 39
Что выведет код при оптимизации -O2?
```cpp
std::vector<int> CreateVector() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    return v;
}

int main() {
    auto v1 = CreateVector();
    auto v2 = CreateVector();
    std::cout << v1.size() << " " << v2.size();
    return 0;
}
```
A) 5 5
B) 0 0
C) 5 0
D) 0 5

## Вопрос 40
Какой из следующих подходов к передаче параметров является наиболее универсальным для шаблонных функций?
```cpp
A) template<typename T> void func(T t) { process(std::move(t)); }
B) template<typename T> void func(const T& t) { process(t); }
C) template<typename T> void func(T&& t) { process(std::forward<T>(t)); }
D) template<typename T> void func(T* t) { process(*t); }
``` 