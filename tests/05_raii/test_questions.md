# Тест по теме: RAII (Resource Acquisition Is Initialization) в C++

**Всего вопросов: 35** (от простого к сложному)

## Вопрос 1 (Простой)
Что означает аббревиатура RAII?

```cpp
class File {
    FILE* handle_;
public:
    File(const char* name) : handle_(fopen(name, "r")) {}
    ~File() { fclose(handle_); }
};
```

**Варианты ответов:**
A) Resource Allocation Is Initialization
B) Resource Acquisition Is Initialization
C) Resource Allocation In Initialization
D) Resource Access Is Initialization

---

## Вопрос 2 (Простой)
Какой основной принцип RAII?

```cpp
class Resource {
    int* data_;
public:
    Resource() : data_(new int[100]) {}
    ~Resource() { delete[] data_; }
};
```

**Варианты ответов:**
A) Ресурсы выделяются в конструкторе и освобождаются в деструкторе
B) Ресурсы выделяются в деструкторе и освобождаются в конструкторе
C) Ресурсы выделяются и освобождаются вручную
D) Ресурсы управляются автоматически компилятором

---

## Вопрос 3 (Простой)
Что произойдет с ресурсом при выходе из области видимости RAII-объекта?

```cpp
void func() {
    std::unique_ptr<int> ptr(new int(42));
    // Что произойдет с памятью при выходе?
}
```

**Варианты ответов:**
A) Память останется выделенной
B) Память автоматически освободится в деструкторе
C) Память нужно освободить вручную
D) Неопределенное поведение

---

## Вопрос 4 (Простой)
Почему RAII защищает от утечек памяти?

```cpp
void func() {
    std::unique_ptr<int> ptr(new int(42));
    throw std::exception();  // Исключение
    // Что с памятью?
}
```

**Варианты ответов:**
A) Память утечет, т.к. исключение прервало выполнение
B) Память автоматически освободится при раскрутке стека
C) Нужно обработать исключение и освободить память вручную
D) Неопределенное поведение

---

## Вопрос 5 (Средний)
Что произойдет при компиляции следующего кода?

```cpp
class File {
    FILE* handle_;
public:
    File(const char* name) : handle_(fopen(name, "r")) {}
    ~File() { fclose(handle_); }
};

void func() {
    File f1("file1.txt");
    File f2 = f1;  // Что здесь?
}
```

**Варианты ответов:**
A) Код скомпилируется и создастся копия файла
B) Ошибка компиляции: нужно запретить копирование
C) Неопределенное поведение: двойное закрытие файла
D) Предупреждение компилятора

---

## Вопрос 6 (Средний)
Как правильно реализовать RAII для мьютекса?

```cpp
class LockGuard {
    std::mutex& mutex_;
public:
    explicit LockGuard(std::mutex& m) : mutex_(m) {
        // Что здесь?
    }
    ~LockGuard() {
        // Что здесь?
    }
};
```

**Варианты ответов:**
A) В конструкторе: `mutex_.unlock()`, в деструкторе: `mutex_.lock()`
B) В конструкторе: `mutex_.lock()`, в деструкторе: `mutex_.unlock()`
C) В конструкторе: ничего, в деструкторе: `mutex_.lock()`
D) В конструкторе: `mutex_.lock()`, в деструкторе: ничего

---

## Вопрос 7 (Средний)
Что такое "правило нуля" (Rule of Zero)?

```cpp
class Modern {
    std::string str_;
    std::vector<int> vec_;
    std::unique_ptr<Resource> ptr_;
    // Нужны ли деструктор, конструктор копирования, оператор присваивания?
};
```

**Варианты ответов:**
A) Нужны все три: деструктор, конструктор копирования, оператор присваивания
B) Не нужны, т.к. все члены - RAII-типы, которые управляют ресурсами сами
C) Нужен только деструктор
D) Нужны конструктор копирования и оператор присваивания

---

## Вопрос 8 (Средний)
В каком порядке уничтожаются члены класса?

```cpp
class Order {
    std::unique_ptr<A> a_;
    std::unique_ptr<B> b_;
    std::unique_ptr<C> c_;
    // В каком порядке вызываются деструкторы?
};
```

**Варианты ответов:**
A) a_, b_, c_ (в порядке объявления)
B) c_, b_, a_ (в обратном порядке объявления)
C) Порядок не определен
D) Все одновременно

---

## Вопрос 9 (Средний)
Что произойдет при компиляции следующего кода?

```cpp
void processFile() {
    FILE* file = fopen("data.txt", "r");
    // Обработка...
    fclose(file);  // Что если здесь будет исключение?
}
```

**Варианты ответов:**
A) Код безопасен, файл всегда закроется
B) Если исключение произойдет до fclose, файл останется открытым
C) Ошибка компиляции
D) Предупреждение компилятора

---

## Вопрос 10 (Средний)
Какой стандартный класс использует RAII для управления мьютексом?

```cpp
// Какой класс автоматически блокирует и разблокирует мьютекс?
```

**Варианты ответов:**
A) `std::mutex`
B) `std::lock_guard<std::mutex>`
C) `std::thread`
D) `std::atomic`

---

## Вопрос 11 (Средний)
Что произойдет при выполнении следующего кода?

```cpp
class Leaky {
    int* data_ = new int[1000];
    // Нет деструктора
};

void func() {
    Leaky l;
    // Что с памятью?
}
```

**Варианты ответов:**
A) Память автоматически освободится
B) Утечка памяти
C) Ошибка компиляции
D) Неопределенное поведение

---

## Вопрос 12 (Средний)
Как правильно использовать RAII для файла?

```cpp
class File {
    FILE* handle_;
public:
    File(const char* name) : handle_(fopen(name, "r")) {
        // Что нужно проверить?
    }
    ~File() { if (handle_) fclose(handle_); }
};
```

**Варианты ответов:**
A) Ничего проверять не нужно
B) Проверить, что handle_ не nullptr, иначе бросить исключение
C) Проверить, что handle_ не nullptr, иначе вернуть ошибку
D) Проверить размер файла

---

## Вопрос 13 (Средний)
Что произойдет при компиляции следующего кода?

```cpp
class Resource {
    std::unique_ptr<int[]> data_;
public:
    Resource() : data_(new int[1000]) {}
    // Нужен ли деструктор?
};
```

**Варианты ответов:**
A) Нужен деструктор для освобождения памяти
B) Деструктор не нужен, unique_ptr сам освободит память
C) Нужен деструктор, но он должен быть пустым
D) Ошибка компиляции без деструктора

---

## Вопрос 14 (Средний)
Какой smart pointer использует RAII для управления памятью?

```cpp
// Какой класс автоматически освобождает память?
```

**Варианты ответов:**
A) `int*`
B) `std::unique_ptr<int>`
C) `std::reference_wrapper<int>`
D) `int&`

---

## Вопрос 15 (Средний)
Что произойдет при выполнении следующего кода?

```cpp
void unsafeFunction(std::mutex& m) {
    m.lock();
    // Если здесь будет исключение?
    m.unlock();
}
```

**Варианты ответов:**
A) Мьютекс автоматически разблокируется
B) Мьютекс останется заблокированным при исключении
C) Ошибка компиляции
D) Неопределенное поведение

---

## Вопрос 16 (Сложный)
Как правильно реализовать RAII-обёртку для кастомного ресурса?

```cpp
class CustomResource {
    // Ресурс, требующий освобождения через release()
public:
    void acquire();
    void release();
};

class RAIIWrapper {
    CustomResource* res_;
public:
    // Как правильно реализовать?
};
```

**Варианты ответов:**
A) Вызвать acquire() в конструкторе, release() в деструкторе
B) Вызвать release() в конструкторе, acquire() в деструкторе
C) Вызвать acquire() и release() в конструкторе
D) Не использовать RAII для кастомных ресурсов

---

## Вопрос 17 (Сложный)
Что произойдет при компиляции следующего кода?

```cpp
class File {
    FILE* handle_;
public:
    File(const char* name) : handle_(fopen(name, "r")) {
        if (!handle_) throw std::runtime_error("Failed");
    }
    ~File() { fclose(handle_); }
    
    File(const File&) = delete;
    File& operator=(const File&) = delete;
    
    File(File&& other) : handle_(other.handle_) {
        other.handle_ = nullptr;
    }
};

void func() {
    File f1("file1.txt");
    File f2 = std::move(f1);  // Правильно ли?
}
```

**Варианты ответов:**
A) Код правильный, файл будет корректно закрыт
B) Ошибка: нужно реализовать оператор присваивания перемещением
C) Неопределенное поведение: двойное закрытие файла
D) Утечка ресурса

---

## Вопрос 18 (Сложный)
Как правильно использовать кастомный делитер с unique_ptr?

```cpp
auto deleter = [](FILE* f) { fclose(f); };
// Как правильно объявить unique_ptr?
```

**Варианты ответов:**
A) `std::unique_ptr<FILE> file(fopen("data.txt", "r"), deleter);`
B) `std::unique_ptr<FILE, decltype(deleter)> file(fopen("data.txt", "r"), deleter);`
C) `std::unique_ptr<FILE*> file(fopen("data.txt", "r"), deleter);`
D) Нельзя использовать кастомный делитер

---

## Вопрос 19 (Сложный)
Что произойдет при выполнении следующего кода?

```cpp
class Resource {
    int* data_;
public:
    Resource() : data_(new int(42)) {}
    ~Resource() { delete data_; }
    
    Resource(const Resource& other) : data_(new int(*other.data_)) {}
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            delete data_;
            data_ = new int(*other.data_);
        }
        return *this;
    }
};

void func() {
    Resource r1;
    Resource r2 = r1;  // Что здесь?
    // Что произойдет при выходе?
}
```

**Варианты ответов:**
A) Ошибка компиляции
B) Код правильный, оба ресурса корректно освободятся
C) Неопределенное поведение: двойное удаление
D) Утечка памяти

---

## Вопрос 20 (Сложный)
Как правильно реализовать exception-safe код с RAII?

```cpp
void safe() {
    std::unique_ptr<Resource> res(new Resource());
    // Что если здесь будет исключение?
    res->doSomething();
}
```

**Варианты ответов:**
A) Нужно обернуть в try-catch
B) Память автоматически освободится при раскрутке стека
C) Нужно вызвать delete вручную перед исключением
D) Исключения не могут возникнуть

---

## Вопрос 21 (Сложный)
Что произойдет при компиляции следующего кода?

```cpp
class Container {
    std::vector<int> data_;
public:
    Container() {
        data_.reserve(1000);
        // Нужен ли деструктор?
    }
};
```

**Варианты ответов:**
A) Нужен деструктор для освобождения памяти вектора
B) Деструктор не нужен, vector сам управляет памятью
C) Нужен деструктор, но он должен быть пустым
D) Ошибка компиляции без деструктора

---

## Вопрос 22 (Сложный)
Как правильно реализовать RAII для нескольких ресурсов?

```cpp
class MultiResource {
    FILE* file_;
    int* data_;
    std::mutex* mutex_;
public:
    MultiResource() {
        file_ = fopen("data.txt", "r");
        data_ = new int[100];
        mutex_ = new std::mutex();
        // Что если один из ресурсов не выделится?
    }
    ~MultiResource() {
        // Как правильно освободить?
    }
};
```

**Варианты ответов:**
A) Освобождать все ресурсы в деструкторе без проверок
B) Проверять каждый ресурс перед освобождением, использовать try-catch в конструкторе
C) Использовать только один ресурс
D) Не использовать RAII для нескольких ресурсов

---

## Вопрос 23 (Сложный)
Что произойдет при выполнении следующего кода?

```cpp
class Resource {
    std::shared_ptr<int> data_;
public:
    Resource() : data_(std::make_shared<int>(42)) {}
    // Нет деструктора
};

void func() {
    Resource r1;
    {
        Resource r2 = r1;  // Копирование
        // Что с памятью при выходе из блока?
    }
    // Что с памятью здесь?
}
```

**Варианты ответов:**
A) Память освободится при выходе из блока
B) Память освободится только при выходе из func()
C) Утечка памяти
D) Неопределенное поведение

---

## Вопрос 24 (Сложный)
Как правильно использовать RAII с placement new?

```cpp
alignas(MyClass) char buffer[sizeof(MyClass)];
MyClass* obj = new (buffer) MyClass();
// Как правильно освободить?
```

**Варианты ответов:**
A) `delete obj;`
B) `obj->~MyClass();` (явный вызов деструктора)
C) `free(buffer);`
D) Память освободится автоматически

---

## Вопрос 25 (Сложный)
Что произойдет при компиляции следующего кода?

```cpp
class File {
    FILE* handle_;
public:
    File(const char* name) : handle_(fopen(name, "r")) {
        if (!handle_) throw std::runtime_error("Failed");
    }
    ~File() {
        if (handle_) fclose(handle_);
    }
    
    File(const File&) = default;  // Разрешить копирование?
    File& operator=(const File&) = default;
};

void func() {
    File f1("file1.txt");
    File f2 = f1;  // Что здесь?
}
```

**Варианты ответов:**
A) Код правильный, файл будет скопирован
B) Неопределенное поведение: двойное закрытие файла
C) Ошибка компиляции
D) Утечка ресурса

---

## Вопрос 26 (Сложный)
Как правильно реализовать RAII для ресурса, который может быть пустым?

```cpp
class OptionalResource {
    Resource* res_ = nullptr;
public:
    OptionalResource() = default;
    OptionalResource(const char* name) : res_(acquire(name)) {}
    ~OptionalResource() {
        // Что здесь?
    }
};
```

**Варианты ответов:**
A) `if (res_) release(res_);`
B) `release(res_);` (без проверки)
C) Ничего не делать
D) `delete res_;`

---

## Вопрос 27 (Сложный)
Что произойдет при выполнении следующего кода?

```cpp
class LockGuard {
    std::mutex& mutex_;
    bool locked_ = false;
public:
    explicit LockGuard(std::mutex& m) : mutex_(m) {
        mutex_.lock();
        locked_ = true;
    }
    ~LockGuard() {
        if (locked_) mutex_.unlock();
    }
    
    void unlock() {
        if (locked_) {
            mutex_.unlock();
            locked_ = false;
        }
    }
};

void func() {
    std::mutex m;
    {
        LockGuard lock(m);
        lock.unlock();  // Раннее разблокирование
        // Что произойдет при выходе из блока?
    }
}
```

**Варианты ответов:**
A) Мьютекс будет разблокирован дважды
B) Мьютекс будет разблокирован один раз корректно
C) Неопределенное поведение
D) Ошибка компиляции

---

## Вопрос 28 (Сложный)
Как правильно использовать RAII с наследованием?

```cpp
class BaseResource {
protected:
    int* data_;
public:
    BaseResource() : data_(new int(42)) {}
    virtual ~BaseResource() { delete data_; }
};

class DerivedResource : public BaseResource {
    int* extra_;
public:
    DerivedResource() : extra_(new int(100)) {}
    // Что нужно в деструкторе?
};
```

**Варианты ответов:**
A) `~DerivedResource() { delete extra_; }`
B) `~DerivedResource() { delete data_; delete extra_; }`
C) Деструктор не нужен
D) Виртуальный деструктор в базовом классе достаточен

---

## Вопрос 29 (Сложный)
Что произойдет при компиляции следующего кода?

```cpp
class Resource {
    std::unique_ptr<int> data_;
public:
    Resource() : data_(std::make_unique<int>(42)) {}
    
    Resource(const Resource& other) {
        // Как правильно скопировать?
    }
};
```

**Варианты ответов:**
A) `data_ = other.data_;` (копирование unique_ptr)
B) `data_ = std::make_unique<int>(*other.data_);` (создание нового)
C) `data_ = std::move(other.data_);` (перемещение)
D) Копирование unique_ptr невозможно

---

## Вопрос 30 (Сложный)
Как правильно реализовать RAII для ресурса с отложенной инициализацией?

```cpp
class LazyResource {
    Resource* res_ = nullptr;
public:
    void initialize(const char* name) {
        // Как правильно инициализировать?
    }
    ~LazyResource() {
        // Как правильно освободить?
    }
};
```

**Варианты ответов:**
A) Всегда проверять res_ перед освобождением
B) Освобождать без проверки
C) Использовать только в конструкторе
D) Не использовать RAII для отложенной инициализации

---

## Вопрос 31 (Сложный)
Что произойдет при выполнении следующего кода?

```cpp
class File {
    FILE* handle_;
public:
    File(const char* name) : handle_(fopen(name, "r")) {
        if (!handle_) throw std::runtime_error("Failed");
    }
    ~File() { 
        if (handle_) {
            fclose(handle_);
            handle_ = nullptr;
        }
    }
    
    File(File&& other) noexcept : handle_(other.handle_) {
        other.handle_ = nullptr;
    }
    
    File& operator=(File&& other) noexcept {
        if (this != &other) {
            if (handle_) fclose(handle_);
            handle_ = other.handle_;
            other.handle_ = nullptr;
        }
        return *this;
    }
};

void func() {
    File f1("file1.txt");
    File f2 = std::move(f1);
    // Что с f1.handle_?
}
```

**Варианты ответов:**
A) f1.handle_ = nullptr, файл будет закрыт при уничтожении f2
B) f1.handle_ указывает на файл, будет двойное закрытие
C) Неопределенное поведение
D) Ошибка компиляции

---

## Вопрос 32 (Сложный)
Как правильно использовать RAII с виртуальными функциями?

```cpp
class Base {
protected:
    int* data_;
public:
    Base() : data_(new int(42)) {}
    virtual ~Base() { delete data_; }
};

class Derived : public Base {
    int* extra_;
public:
    Derived() : extra_(new int(100)) {}
    ~Derived() { delete extra_; }
};

void func() {
    Base* ptr = new Derived();
    delete ptr;  // Что произойдет?
}
```

**Варианты ответов:**
A) Будет вызван только деструктор Base, утечка памяти
B) Будет вызван деструктор Derived, затем Base, все корректно
C) Неопределенное поведение
D) Ошибка компиляции

---

## Вопрос 33 (Сложный)
Что произойдет при компиляции следующего кода?

```cpp
class Resource {
    std::shared_ptr<int> data_;
public:
    Resource() : data_(std::make_shared<int>(42)) {}
    // Нужен ли деструктор?
};

void func() {
    Resource r1;
    {
        Resource r2 = r1;  // Копирование shared_ptr
    }
    // Что с памятью?
}
```

**Варианты ответов:**
A) Память освободится при выходе из блока
B) Память освободится только при выходе из func()
C) Утечка памяти
D) Деструктор обязателен для shared_ptr

---

## Вопрос 34 (Сложный)
Как правильно реализовать RAII для ресурса, который требует специальной последовательности освобождения?

```cpp
class ComplexResource {
    ResourceA* a_;
    ResourceB* b_;
public:
    ComplexResource() {
        a_ = acquireA();
        b_ = acquireB(a_);  // B зависит от A
    }
    ~ComplexResource() {
        // В каком порядке освобождать?
    }
};
```

**Варианты ответов:**
A) Освобождать в порядке объявления: сначала a_, потом b_
B) Освобождать в обратном порядке: сначала b_, потом a_
C) Порядок не важен
D) Освобождать одновременно

---

## Вопрос 35 (Сложный)
Что произойдет при выполнении следующего кода?

```cpp
class Modern {
    std::string str_;
    std::vector<int> vec_;
    std::unique_ptr<Resource> ptr_;
    // Нет явных деструктора, конструктора копирования, оператора присваивания
};

void func() {
    Modern m1;
    Modern m2 = m1;  // Что здесь?
}
```

**Варианты ответов:**
A) Код скомпилируется, создастся копия
B) Ошибка компиляции: unique_ptr нельзя копировать
C) Неопределенное поведение
D) Предупреждение компилятора

---

## Правильные ответы

1. **B** - Resource Acquisition Is Initialization
2. **A** - Ресурсы выделяются в конструкторе и освобождаются в деструкторе
3. **B** - Память автоматически освободится в деструкторе
4. **B** - Память автоматически освободится при раскрутке стека
5. **C** - Неопределенное поведение: двойное закрытие файла
6. **B** - В конструкторе: `mutex_.lock()`, в деструкторе: `mutex_.unlock()`
7. **B** - Не нужны, т.к. все члены - RAII-типы, которые управляют ресурсами сами
8. **B** - c_, b_, a_ (в обратном порядке объявления)
9. **B** - Если исключение произойдет до fclose, файл останется открытым
10. **B** - `std::lock_guard<std::mutex>`
11. **B** - Утечка памяти
12. **B** - Проверить, что handle_ не nullptr, иначе бросить исключение
13. **B** - Деструктор не нужен, unique_ptr сам освободит память
14. **B** - `std::unique_ptr<int>`
15. **B** - Мьютекс останется заблокированным при исключении
16. **A** - Вызвать acquire() в конструкторе, release() в деструкторе
17. **A** - Код правильный, файл будет корректно закрыт
18. **B** - `std::unique_ptr<FILE, decltype(deleter)> file(fopen("data.txt", "r"), deleter);`
19. **B** - Код правильный, оба ресурса корректно освободятся
20. **B** - Память автоматически освободится при раскрутке стека
21. **B** - Деструктор не нужен, vector сам управляет памятью
22. **B** - Проверять каждый ресурс перед освобождением, использовать try-catch в конструкторе
23. **B** - Память освободится только при выходе из func()
24. **B** - `obj->~MyClass();` (явный вызов деструктора)
25. **B** - Неопределенное поведение: двойное закрытие файла
26. **A** - `if (res_) release(res_);`
27. **B** - Мьютекс будет разблокирован один раз корректно
28. **A** - `~DerivedResource() { delete extra_; }`
29. **B** - `data_ = std::make_unique<int>(*other.data_);` (создание нового)
30. **A** - Всегда проверять res_ перед освобождением
31. **A** - f1.handle_ = nullptr, файл будет закрыт при уничтожении f2
32. **B** - Будет вызван деструктор Derived, затем Base, все корректно
33. **B** - Память освободится только при выходе из func()
34. **B** - Освобождать в обратном порядке: сначала b_, потом a_
35. **B** - Ошибка компиляции: unique_ptr нельзя копировать


