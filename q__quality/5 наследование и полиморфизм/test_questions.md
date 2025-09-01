# Тест по наследованию и полиморфизму в C++

## Инструкции
- Выберите один правильный ответ для каждого вопроса
- Вопросы рассчитаны на знание C++ стандарта не выше C++17
- Уровень сложности: средний/сложный

---

**Вопрос 1:** Что произойдет при выполнении следующего кода?

```cpp
class Base {
public:
    void func() { std::cout << "Base::func"; }
};

class Derived : public Base {
public:
    void func() { std::cout << "Derived::func"; }
};

int main() {
    Derived d;
    Base* ptr = &d;
    ptr->func();
}
```

a) Выведет "Base::func"  
b) Выведет "Derived::func"  
c) Ошибка компиляции  
d) Неопределенное поведение  

---

**Вопрос 2:** Какой спецификатор доступа следует использовать для деструктора базового класса при полиморфном использовании?

a) private  
b) protected  
c) public virtual  
d) private virtual  

---

**Вопрос 3:** Что выведет следующий код?

```cpp
class Animal {
public:
    virtual ~Animal() = default;
    virtual void speak() { std::cout << "Animal speaks"; }
};

class Dog : public Animal {
public:
    void speak() override { std::cout << "Woof"; }
};

class Puppy : public Dog {
public:
    void speak() override final { std::cout << "Yip"; }
};

void test(Animal* a) { a->speak(); }

int main() {
    Puppy p;
    test(&p);
}
```

a) "Animal speaks"  
b) "Woof"  
c) "Yip"  
d) Ошибка компиляции  

---

**Вопрос 4:** Какой размер в памяти будет занимать объект класса B?

```cpp
class A {
    int x;
};

class B {
    virtual ~B() = default;
    int x;
};
```

a) 4 байта  
b) 8 байт  
c) 12 байт  
d) Больше 8 байт  

---

**Вопрос 5:** Что означает ключевое слово `override` в C++11?

a) Переопределяет любой метод базового класса  
b) Гарантирует, что метод переопределяет виртуальный метод базового класса  
c) Делает метод виртуальным  
d) Запрещает дальнейшее переопределение метода  

---

**Вопрос 6:** Что произойдет при выполнении следующего кода?

```cpp
class Shape {
public:
    virtual double area() = 0;
};

class Circle : public Shape {
public:
    Circle(double r) : radius(r) {}
    double area() override { return 3.14 * radius * radius; }
private:
    double radius;
};

int main() {
    Shape s;
    return 0;
}
```

a) Программа выполнится успешно  
b) Ошибка компиляции - нельзя создать объект абстрактного класса  
c) Ошибка компиляции - отсутствует конструктор  
d) Неопределенное поведение  

---

**Вопрос 7:** Какие отношения между классами выражает публичное наследование?

a) "Содержит" (has-a)  
b) "Является" (is-a)  
c) "Использует" (uses-a)  
d) "Реализован посредством"  

---

**Вопрос 8:** Что выведет следующий код?

```cpp
class Exception1 : public std::exception {};
class Exception2 : public Exception1 {};

int main() {
    try {
        throw Exception2{};
    } catch (const Exception1& e) {
        std::cout << "Caught Exception1";
    } catch (const Exception2& e) {
        std::cout << "Caught Exception2";
    }
}
```

a) "Caught Exception1"  
b) "Caught Exception2"  
c) Ошибка компиляции  
d) Исключение не будет поймано  

---

**Вопрос 9:** В каких случаях следует использовать приватное наследование?

a) Для выражения отношения "является"  
b) Для выражения отношения "реализован посредством"  
c) Для скрытия методов базового класса  
d) Никогда не следует использовать  

---

**Вопрос 10:** Что произойдет при выполнении следующего кода?

```cpp
class Base {
public:
    Base() { std::cout << "Base ctor "; }
    ~Base() { std::cout << "Base dtor "; }
};

class Derived : public Base {
public:
    Derived() { std::cout << "Derived ctor "; }
    ~Derived() { std::cout << "Derived dtor "; }
};

int main() {
    Derived d;
}
```

a) "Base ctor Derived ctor Derived dtor Base dtor"  
b) "Derived ctor Base ctor Base dtor Derived dtor"  
c) "Base ctor Derived ctor Base dtor Derived dtor"  
d) "Derived ctor Base ctor Derived dtor Base dtor"  

---

**Вопрос 11:** Какой спецификатор доступа имеют members базового класса в производном классе при protected наследовании?

a) public members становятся protected, protected остаются protected  
b) Все members становятся protected  
c) public members становятся private, protected остаются protected  
d) Все members становятся private  

---

**Вопрос 12:** Что выведет следующий код?

```cpp
class A {
public:
    virtual void f() { std::cout << "A::f "; }
    void g() { f(); }
};

class B : public A {
public:
    void f() override { std::cout << "B::f "; }
};

int main() {
    B b;
    A* ptr = &b;
    ptr->g();
}
```

a) "A::f"  
b) "B::f"  
c) Ошибка компиляции  
d) Неопределенное поведение  

---

**Вопрос 13:** Что такое виртуальное наследование и когда оно используется?

a) Для создания виртуальных методов  
b) Для решения проблемы ромбовидного наследования  
c) Для создания абстрактных классов  
d) Для множественного наследования  

---

**Вопрос 14:** Что произойдет при выполнении следующего кода?

```cpp
class Base {
public:
    virtual void process() { std::cout << "Base::process"; }
};

class Derived : public Base {
public:
    void process() const override { std::cout << "Derived::process"; }
};
```

a) Код скомпилируется и будет работать корректно  
b) Ошибка компиляции - несовпадение сигнатур методов  
c) Метод в Derived скроет метод в Base  
d) Неопределенное поведение  

---

**Вопрос 15:** Какой результат даст dynamic_cast<Derived*>(base_ptr) если base_ptr указывает на объект другого типа?

a) Неопределенное поведение  
b) Ошибка компиляции  
c) nullptr  
d) Указатель на объект Base  

---

**Вопрос 16:** Что выведет следующий код?

```cpp
class Animal {
public:
    Animal(const std::string& name) : name_(name) {}
protected:
    std::string name_;
};

class Dog : public Animal {
public:
    Dog(const std::string& name) : Animal(name) {}
    void bark() { std::cout << name_ << " barks"; }
};

int main() {
    Dog d("Rex");
    d.bark();
}
```

a) "Rex barks"  
b) " barks"  
c) Ошибка компиляции  
d) Неопределенное поведение  

---

**Вопрос 17:** Что означает "срезка объекта" (object slicing) в контексте наследования?

a) Удаление части объекта из памяти  
b) Потеря данных производного класса при копировании в базовый класс  
c) Разделение объекта на несколько частей  
d) Оптимизация компилятором размера объекта  

---

**Вопрос 18:** Что произойдет при выполнении следующего кода?

```cpp
class Interface {
public:
    virtual ~Interface() = default;
    virtual void method() = 0;
};

class Implementation : public Interface {
public:
    void method() override { std::cout << "Implemented"; }
};

class Wrapper : private Implementation {
public:
    void callMethod() { method(); }
};

int main() {
    Wrapper w;
    Interface* ptr = &w;  // Строка X
    return 0;
}
```

a) Код выполнится успешно  
b) Ошибка компиляции на строке X  
c) Ошибка компиляции в классе Wrapper  
d) Неопределенное поведение  

---

**Вопрос 19:** Какой паттерн проектирования демонстрирует следующий код?

```cpp
class CaffeineBeverage {
public:
    void prepareBeverage() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }
protected:
    virtual void brew() = 0;
    virtual void addCondiments() = 0;
private:
    void boilWater() { /* implementation */ }
    void pourInCup() { /* implementation */ }
};
```

a) Strategy  
b) Template Method  
c) Factory Method  
d) Observer  

---

**Вопрос 20:** Что выведет следующий код?

```cpp
class A {
public:
    virtual void func() { std::cout << "A"; }
};

class B : public A {
public:
    void func() override { 
        A::func(); 
        std::cout << "B"; 
    }
};

class C : public B {
public:
    void func() override { 
        B::func(); 
        std::cout << "C"; 
    }
};

int main() {
    C c;
    A* ptr = &c;
    ptr->func();
}
```

a) "A"  
b) "ABC"  
c) "C"  
d) "CAB"  

---

**Вопрос 21:** Какое ключевое слово используется для запрета дальнейшего наследования от класса?

a) final  
b) sealed  
c) abstract  
d) override  

---

**Вопрос 22:** Что произойдет при выполнении следующего кода?

```cpp
class Base {
public:
    Base(int x) : value(x) {}
private:
    int value;
};

class Derived : public Base {
public:
    Derived() {}  // Строка X
};
```

a) Код скомпилируется успешно  
b) Ошибка компиляции на строке X - нет конструктора по умолчанию в Base  
c) Ошибка компиляции - приватные члены недоступны  
d) Неопределенное поведение  

---

**Вопрос 23:** В каком порядке вызываются деструкторы в иерархии наследования?

a) От базового к производному  
b) От производного к базовому  
c) В случайном порядке  
d) Одновременно  

---

**Вопрос 24:** Что выведет следующий код?

```cpp
class Base {
public:
    void show() { std::cout << "Base"; }
};

class Derived : public Base {
public:
    void show() { std::cout << "Derived"; }
};

void test(Base b) {
    b.show();
}

int main() {
    Derived d;
    test(d);
}
```

a) "Base"  
b) "Derived"  
c) Ошибка компиляции  
d) Неопределенное поведение  

---

**Вопрос 25:** Что такое CRTP (Curiously Recurring Template Pattern)?

a) Шаблон, где базовый класс наследуется от производного  
b) Шаблон, где класс наследуется от шаблона, параметризованного самим классом  
c) Циклическое наследование между классами  
d) Рекурсивное создание объектов  

---

**Вопрос 26:** Что произойдет при выполнении следующего кода?

```cpp
class A {
public:
    A() { func(); }
    virtual void func() { std::cout << "A::func"; }
};

class B : public A {
public:
    void func() override { std::cout << "B::func"; }
};

int main() {
    B b;
}
```

a) "A::func"  
b) "B::func"  
c) Ошибка компиляции  
d) Неопределенное поведение  

---

**Вопрос 27:** Какой тип исключения выбрасывает dynamic_cast для ссылок при неудачном приведении?

a) std::bad_cast  
b) std::runtime_error  
c) std::exception  
d) std::bad_alloc  

---

**Вопрос 28:** Что выведет следующий код?

```cpp
class Animal {
public:
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void bark() { std::cout << "Woof"; }
};

int main() {
    Animal* animal = new Dog();
    Dog* dog = static_cast<Dog*>(animal);
    dog->bark();
    delete animal;
}
```

a) "Woof"  
b) Ошибка компиляции  
c) Неопределенное поведение  
d) Segmentation fault  

---

**Вопрос 29:** В чем основное различие между std::variant и традиционным полиморфизмом через наследование?

a) std::variant работает быстрее  
b) std::variant не требует виртуальных функций и наследования  
c) std::variant занимает меньше памяти  
d) std::variant поддерживает только примитивные типы  

---

**Вопрос 30:** Что произойдет при выполнении следующего кода?

```cpp
class A {
public:
    virtual void f() = 0;
};

class B : public A {
public:
    void f() override { std::cout << "B::f"; }
};

class C : public B {
    // Не переопределяет f()
};

int main() {
    C c;
    c.f();
}
```

a) Ошибка компиляции - C абстрактный класс  
b) "B::f"  
c) Ошибка компиляции - нет реализации f() в C  
d) Неопределенное поведение  

---

**Вопрос 31:** Какой принцип SOLID нарушается в следующем коде?

```cpp
class Bird {
public:
    virtual void fly() = 0;
    virtual void eat() = 0;
};

class Penguin : public Bird {
public:
    void fly() override { 
        throw std::runtime_error("Penguins can't fly"); 
    }
    void eat() override { /* implementation */ }
};
```

a) Single Responsibility Principle  
b) Open/Closed Principle  
c) Liskov Substitution Principle  
d) Interface Segregation Principle  

---

**Вопрос 32:** Что выведет следующий код?

```cpp
class Base {
public:
    virtual void func() { std::cout << "Base"; }
};

class Middle : public Base {
public:
    void func() override final { std::cout << "Middle"; }
};

class Derived : public Middle {
public:
    void func() override { std::cout << "Derived"; }  // Строка X
};
```

a) Код скомпилируется, выведет "Derived"  
b) Ошибка компиляции на строке X - нельзя переопределить final метод  
c) Выведет "Middle"  
d) Неопределенное поведение  

---

**Вопрос 33:** Что такое виртуальная таблица (vtable)?

a) Структура данных для хранения виртуальных функций объекта  
b) Таблица всех объектов в программе  
c) Механизм сборки мусора в C++  
d) Способ оптимизации виртуальных вызовов  

---

**Вопрос 34:** Что произойдет при выполнении следующего кода?

```cpp
class Base {
protected:
    int value = 10;
};

class Derived1 : public virtual Base {};
class Derived2 : public virtual Base {};

class Final : public Derived1, public Derived2 {
public:
    void print() { std::cout << value; }
};

int main() {
    Final f;
    f.print();
}
```

a) "10"  
b) Ошибка компиляции - неоднозначность  
c) "1010"  
d) Неопределенное поведение  

---

**Вопрос 35:** Какой метод следует объявить как `[[nodiscard]]` в C++17?

a) Конструктор  
b) Деструктор  
c) Метод, возвращающий важный статус операции  
d) Виртуальный метод  

---

**Вопрос 36:** Что выведет следующий код?

```cpp
class A {
public:
    void func() { std::cout << "A"; }
};

class B {
public:
    void func() { std::cout << "B"; }
};

class C : public A, public B {
public:
    void test() {
        func();  // Строка X
    }
};
```

a) "A"  
b) "B"  
c) Ошибка компиляции на строке X - неоднозначность  
d) "AB"  

---

**Вопрос 37:** В каком случае следует использовать композицию вместо наследования?

a) Когда есть отношение "является"  
b) Когда нужен полиморфизм  
c) Когда есть отношение "содержит" или "использует"  
d) Когда нужны виртуальные функции  

---

**Вопрос 38:** Что произойдет при выполнении следующего кода?

```cpp
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

void drawShape(Shape shape) {  // Передача по значению
    shape.draw();
}

class Circle : public Shape {
public:
    void draw() const override { std::cout << "Circle"; }
};

int main() {
    Circle c;
    drawShape(c);
}
```

a) "Circle"  
b) Ошибка компиляции - нельзя создать объект абстрактного класса  
c) Ошибка компиляции - другая причина  
d) Неопределенное поведение  

---

**Вопрос 39:** Что такое "алмазная проблема" в множественном наследовании?

a) Проблема производительности при множественном наследовании  
b) Ситуация, когда класс наследуется от двух классов с общим предком  
c) Невозможность создания объектов при множественном наследовании  
d) Проблема с доступом к приватным членам  

---

**Вопрос 40:** Что выведет следующий код?

```cpp
class Resource {
public:
    Resource() { std::cout << "Acquire "; }
    ~Resource() { std::cout << "Release "; }
};

class Manager {
public:
    Manager() : resource() { std::cout << "Manager "; }
    ~Manager() { std::cout << "~Manager "; }
private:
    Resource resource;
};

int main() {
    Manager m;
    return 0;
}
```

a) "Acquire Manager ~Manager Release"  
b) "Manager Acquire Release ~Manager"  
c) "Acquire Manager Release ~Manager"  
d) "Manager Acquire ~Manager Release"  

---

## Конец теста

Для получения правильных ответов см. файл `answers.md` в той же папке. 