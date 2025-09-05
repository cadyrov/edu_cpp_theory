# Полиморфизм

## Определение
Полиморфизм в C++ - механизм, позволяющий использовать единый интерфейс для работы с различными типами объектов. Включает в себя статический (compile-time) и динамический (runtime) полиморфизм.

## Зачем это нужно
- Абстракция и инкапсуляция поведения
- Гибкое расширение функциональности
- Упрощение поддержки кода
- Реализация паттернов проектирования
- Создание модульных систем

## Примеры

### ✅ Хорошо
```cpp
// Базовый класс с виртуальным интерфейсом
class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual void draw() const = 0;
};

// Конкретные реализации
class Circle : public Shape {
    double radius_;
public:
    explicit Circle(double r) : radius_(r) {}
    
    double area() const override {
        return M_PI * radius_ * radius_;
    }
    
    void draw() const override {
        // Реализация отрисовки
    }
};

// Фабричный метод
class ShapeFactory {
public:
    static std::unique_ptr<Shape> create(const std::string& type) {
        if (type == "circle")
            return std::make_unique<Circle>(1.0);
        // Другие типы...
        return nullptr;
    }
};

// CRTP для статического полиморфизма
template<typename Derived>
class Logger {
public:
    void log(const std::string& message) {
        static_cast<Derived*>(this)->log_impl(message);
    }
};

class FileLogger : public Logger<FileLogger> {
public:
    void log_impl(const std::string& message) {
        // Запись в файл
    }
};
```

### ❌ Плохо
```cpp
// Отсутствие виртуального деструктора
class Base {
public:
    void process() { }  // Не виртуальный метод
};  // Утечка при delete через Base*

// Неправильное использование override
class Derived : public Base {
    virtual void Process() {  // Опечатка в имени
        // Создаёт новый виртуальный метод
    }
};

// Срезка объекта
class SliceProblem : public Base {
    std::string extra_data_;
};
void wrong(Base base) {  // Передача по значению
    // Объект срезается
}

// Виртуальные функции в конструкторе
class Wrong {
public:
    Wrong() {
        init();  // Вызов виртуальной функции в конструкторе
    }
    virtual void init() = 0;
};
```

## Нюансы использования

### 1. Виртуальные функции
```cpp
class Interface {
public:
    virtual ~Interface() = default;  // Виртуальный деструктор
    
    // Pure virtual функции
    virtual void must_implement() = 0;
    
    // Виртуальные функции с реализацией
    virtual void can_override() {
        // Реализация по умолчанию
    }
};
```

### 2. final и override
```cpp
class Base {
public:
    virtual void interface() = 0;
};

class Derived final : public Base {  // Запрет наследования
    void interface() override {  // Явное указание переопределения
        // Реализация
    }
};
```

### 3. CRTP (Curiously Recurring Template Pattern)
```cpp
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

class Concrete : public Base<Concrete> {
public:
    void implementation() {
        // Реализация
    }
};
```

### 4. Виртуальные таблицы
```cpp
class VTable {
    void* vptr_;  // Указатель на виртуальную таблицу
public:
    virtual void method() = 0;
    // Компилятор создаёт vtable
};
```

### 5. Multiple Inheritance
```cpp
class Interface1 {
public:
    virtual ~Interface1() = default;
    virtual void method1() = 0;
};

class Interface2 {
public:
    virtual ~Interface2() = default;
    virtual void method2() = 0;
};

class Implementation : public Interface1, public Interface2 {
public:
    void method1() override { }
    void method2() override { }
};
```

### 6. Virtual Inheritance
```cpp
class Base {
protected:
    int data_;
};

class Derived1 : virtual public Base { };
class Derived2 : virtual public Base { };

class Final : public Derived1, public Derived2 {
    // Только одна копия Base::data_
};
```

### 7. Type Erasure
```cpp
class Any {
    struct Concept {
        virtual ~Concept() = default;
        virtual void handle() = 0;
    };
    
    template<typename T>
    struct Model : Concept {
        T value_;
        explicit Model(T value) : value_(std::move(value)) {}
        void handle() override { value_.process(); }
    };
    
    std::unique_ptr<Concept> ptr_;
public:
    template<typename T>
    Any(T value) : ptr_(std::make_unique<Model<T>>(std::move(value))) {}
};
```

### 8. Best practices
```cpp
// 1. Используй smart pointers
std::vector<std::unique_ptr<Shape>> shapes;
shapes.push_back(std::make_unique<Circle>(1.0));

// 2. Фабричные методы
class Factory {
public:
    template<typename T, typename... Args>
    static std::unique_ptr<Base> create(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
};

// 3. Интерфейсы
class Interface {
public:
    virtual ~Interface() = default;
    virtual void method() = 0;
protected:
    // Protected non-virtual interface
    void helper() { }
};

// 4. Композиция вместо наследования
class Composite {
    std::unique_ptr<Implementation> impl_;
public:
    void process() {
        impl_->process();
    }
};
```
