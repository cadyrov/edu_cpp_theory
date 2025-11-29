# Тест по теме: Rule of Five (Правило пяти) в C++

**Всего вопросов: 35** (от простого к сложному)

## Вопрос 1 (Простой)
Что такое Rule of Five (Правило пяти)?

```cpp
class Resource {
    // Какие функции нужно определить?
};
```

**Варианты ответов:**
A) Пять конструкторов
B) Деструктор, конструктор копирования, оператор присваивания копированием, конструктор перемещения, оператор присваивания перемещением
C) Пять операторов присваивания
D) Пять деструкторов

---

## Вопрос 2 (Простой)
Если класс определяет деструктор, что еще нужно определить?

```cpp
class Resource {
    int* data_;
public:
    ~Resource() { delete data_; }
    // Что еще нужно?
};
```

**Варианты ответов:**
A) Ничего больше не нужно
B) Конструктор копирования и оператор присваивания
C) Все пять функций (деструктор, копирование, перемещение)
D) Только конструктор копирования

---

## Вопрос 3 (Простой)
Что произойдет, если определить только деструктор без остальных функций?

```cpp
class Wrong {
    int* data_;
public:
    ~Wrong() { delete data_; }
    // Остальные функции используют дефолтную реализацию
};
```

**Варианты ответов:**
A) Код правильный
B) Возможны double-delete или утечки памяти
C) Ошибка компиляции
D) Предупреждение компилятора

---

## Вопрос 4 (Простой)
Что такое Rule of Zero?

```cpp
class Modern {
    std::string str_;
    std::vector<int> vec_;
    std::unique_ptr<Resource> ptr_;
    // Нужны ли пять функций?
};
```

**Варианты ответов:**
A) Нужны все пять функций
B) Не нужно определять ни одну из пяти функций, если все члены - RAII-типы
C) Нужны только деструктор и конструктор копирования
D) Нужны только move операции

---

## Вопрос 5 (Средний)
Какие функции входят в Rule of Five?

```cpp
// Какие пять функций?
```

**Варианты ответов:**
A) Деструктор, конструктор копирования, оператор присваивания копированием, конструктор перемещения, оператор присваивания перемещением
B) Пять конструкторов с разными параметрами
C) Деструктор и четыре оператора присваивания
D) Пять деструкторов для разных случаев

---

## Вопрос 6 (Средний)
Как правильно пометить move операции?

```cpp
class Safe {
    std::string data_;
public:
    Safe(Safe&& other) /* что здесь? */ = default;
    Safe& operator=(Safe&& other) /* что здесь? */ = default;
};
```

**Варианты ответов:**
A) `noexcept`
B) `const`
C) `virtual`
D) Ничего не нужно

---

## Вопрос 7 (Средний)
Что произойдет при компиляции следующего кода?

```cpp
class Resource {
    int* data_;
public:
    Resource(const Resource& other) {
        data_ = new int(*other.data_);
    }
    // Остальные функции не определены
};
```

**Варианты ответов:**
A) Код правильный
B) Нарушение Rule of Five: нужно определить все пять функций
C) Ошибка компиляции
D) Предупреждение компилятора

---

## Вопрос 8 (Средний)
Как правильно реализовать конструктор копирования?

```cpp
class Buffer {
    size_t size_;
    char* data_;
public:
    Buffer(const Buffer& other) {
        // Как правильно скопировать?
    }
};
```

**Варианты ответов:**
A) `data_ = other.data_;` (копирование указателя)
B) `size_ = other.size_; data_ = new char[size_]; std::copy(...);` (глубокое копирование)
C) `*this = other;`
D) `data_ = other.data_; size_ = other.size_;`

---

## Вопрос 9 (Средний)
Как правильно реализовать оператор присваивания копированием?

```cpp
class Resource {
    int* data_;
public:
    Resource& operator=(const Resource& other) {
        // Как правильно?
    }
};
```

**Варианты ответов:**
A) `data_ = other.data_; return *this;`
B) `if (this != &other) { delete data_; data_ = new int(*other.data_); } return *this;`
C) `*this = other; return *this;`
D) `data_ = other.data_;`

---

## Вопрос 10 (Средний)
Что такое copy-and-swap идиома?

```cpp
class Swappable {
    Resource* res_;
public:
    void swap(Swappable& other) noexcept { /* ... */ }
    
    Swappable& operator=(Swappable other) {  // Принимает по значению!
        // Что здесь?
    }
};
```

**Варианты ответов:**
A) `swap(other); return *this;`
B) `*this = other; return *this;`
C) `res_ = other.res_; return *this;`
D) `other.swap(*this); return *this;`

---

## Вопрос 11 (Средний)
Как правильно реализовать конструктор перемещения?

```cpp
class Buffer {
    size_t size_;
    char* data_;
public:
    Buffer(Buffer&& other) noexcept {
        // Как правильно переместить?
    }
};
```

**Варианты ответов:**
A) `data_ = other.data_; size_ = other.size_;`
B) `size_ = other.size_; data_ = other.data_; other.data_ = nullptr; other.size_ = 0;`
C) `*this = std::move(other);`
D) `data_ = std::move(other.data_);`

---

## Вопрос 12 (Средний)
Как правильно реализовать оператор присваивания перемещением?

```cpp
class Resource {
    int* data_;
public:
    Resource& operator=(Resource&& other) noexcept {
        // Как правильно?
    }
};
```

**Варианты ответов:**
A) `data_ = other.data_; return *this;`
B) `if (this != &other) { delete data_; data_ = other.data_; other.data_ = nullptr; } return *this;`
C) `*this = std::move(other); return *this;`
D) `data_ = other.data_;`

---

## Вопрос 13 (Средний)
Что произойдет при компиляции следующего кода?

```cpp
class Incomplete {
    std::unique_ptr<Resource> res_;
public:
    Incomplete(const Incomplete&) = delete;
    Incomplete& operator=(const Incomplete&) = delete;
    // Move операции не определены
};
```

**Варианты ответов:**
A) Код правильный, объект можно перемещать
B) Объект нельзя перемещать, т.к. move операции не определены
C) Ошибка компиляции
D) Неопределенное поведение

---

## Вопрос 14 (Средний)
Как правильно запретить копирование, но разрешить перемещение?

```cpp
class Special {
    // Как запретить копирование, но разрешить перемещение?
};
```

**Варианты ответов:**
A) `Special(const Special&) = delete; Special& operator=(const Special&) = delete; Special(Special&&) = default; Special& operator=(Special&&) = default;`
B) Нельзя запретить копирование
C) Определить только move операции
D) Использовать только `= delete` для копирования

---

## Вопрос 15 (Средний)
Что произойдет при компиляции следующего кода?

```cpp
class Base {
public:
    virtual ~Base() = default;
    // Остальные функции не виртуальные
};
```

**Варианты ответов:**
A) Код правильный, деструктор должен быть виртуальным
B) Все функции должны быть виртуальными
C) Ошибка компиляции
D) Предупреждение компилятора

---

## Вопрос 16 (Сложный)
Как правильно использовать =default для Rule of Five?

```cpp
class Modern {
    std::unique_ptr<Resource> res_;
public:
    // Как правильно использовать =default?
};
```

**Варианты ответов:**
A) `~Modern() = default; Modern(const Modern&) = default; Modern& operator=(const Modern&) = default; Modern(Modern&&) noexcept = default; Modern& operator=(Modern&&) noexcept = default;`
B) Нельзя использовать =default
C) Только для деструктора
D) Только для move операций

---

## Вопрос 17 (Сложный)
Что произойдет при выполнении следующего кода?

```cpp
class Wrong {
    int* data_;
public:
    Wrong() : data_(new int(42)) {}
    ~Wrong() { delete data_; }
    // Остальные функции используют дефолтную реализацию
};

void func() {
    Wrong w1;
    Wrong w2 = w1;  // Что здесь?
}
```

**Варианты ответов:**
A) Код правильный, создастся копия
B) Неопределенное поведение: двойное удаление при выходе
C) Ошибка компиляции
D) Утечка памяти

---

## Вопрос 18 (Сложный)
Как правильно обеспечить strong exception guarantee в операторе присваивания?

```cpp
class Exception {
    std::unique_ptr<Resource> res_;
public:
    Exception& operator=(const Exception& other) {
        // Как обеспечить строгую гарантию?
    }
};
```

**Варианты ответов:**
A) `res_ = std::make_unique<Resource>(*other.res_); return *this;`
B) `auto temp = std::make_unique<Resource>(*other.res_); res_ = std::move(temp); return *this;`
C) `*this = other; return *this;`
D) `res_ = other.res_; return *this;`

---

## Вопрос 19 (Сложный)
Что произойдет при компиляции следующего кода?

```cpp
class Buffer {
    size_t size_;
    char* data_;
public:
    Buffer(Buffer&& other) {
        size_ = other.size_;
        data_ = other.data_;
        other.data_ = nullptr;
    }
    // Что не хватает?
};
```

**Варианты ответов:**
A) Код правильный
B) Нужно добавить `noexcept`
C) Нужно добавить `const`
D) Ошибка компиляции

---

## Вопрос 20 (Сложный)
Как правильно реализовать swap для copy-and-swap?

```cpp
class Swappable {
    Resource* res_;
public:
    void swap(Swappable& other) {
        // Как правильно реализовать?
    }
};
```

**Варианты ответов:**
A) `using std::swap; swap(res_, other.res_);` и пометить `noexcept`
B) `res_ = other.res_;`
C) `*this = other;`
D) `std::swap(res_, other.res_);`

---

## Вопрос 21 (Сложный)
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
    // Move операции не определены
};

void func() {
    Resource r1;
    Resource r2 = std::move(r1);  // Что здесь?
}
```

**Варианты ответов:**
A) Вызовется конструктор копирования
B) Ошибка компиляции: нет конструктора перемещения
C) Неопределенное поведение
D) Утечка памяти

---

## Вопрос 22 (Сложный)
Как правильно использовать copy-and-swap с оператором присваивания?

```cpp
class Container {
    std::vector<int> data_;
public:
    Container& operator=(const Container& other) {
        // Как использовать copy-and-swap?
    }
};
```

**Варианты ответов:**
A) `Container temp(other); swap(temp); return *this;`
B) `data_ = other.data_; return *this;`
C) `*this = other; return *this;`
D) `swap(Container(other)); return *this;`

---

## Вопрос 23 (Сложный)
Что произойдет при компиляции следующего кода?

```cpp
class Base {
public:
    virtual ~Base() = default;
    virtual Base* clone() const = 0;
};

class Derived : public Base {
    int data_;
public:
    Derived* clone() const override {
        return new Derived(*this);
    }
    // Нужны ли пять функций?
};
```

**Варианты ответов:**
A) Нужны все пять функций
B) Нужны только деструктор и конструктор копирования
C) Деструктор уже есть в Base, остальное по умолчанию
D) Нужны только move операции

---

## Вопрос 24 (Сложный)
Как правильно реализовать оператор присваивания с проверкой самоприсваивания?

```cpp
class Resource {
    int* data_;
public:
    Resource& operator=(const Resource& other) {
        // Как правильно проверить самоприсваивание?
    }
};
```

**Варианты ответов:**
A) `if (this != &other) { /* ... */ } return *this;`
B) `if (*this != other) { /* ... */ } return *this;`
C) Проверка не нужна
D) `if (data_ != other.data_) { /* ... */ } return *this;`

---

## Вопрос 25 (Сложный)
Что произойдет при выполнении следующего кода?

```cpp
class Buffer {
    size_t size_;
    char* data_;
public:
    Buffer(Buffer&& other) noexcept
        : size_(other.size_)
        , data_(other.data_)
    {
        other.size_ = 0;
        other.data_ = nullptr;
    }
    
    Buffer& operator=(Buffer&& other) noexcept {
        // Что нужно добавить?
    }
};
```

**Варианты ответов:**
A) `size_ = other.size_; data_ = other.data_; other.size_ = 0; other.data_ = nullptr; return *this;`
B) `if (this != &other) { delete[] data_; size_ = other.size_; data_ = other.data_; other.size_ = 0; other.data_ = nullptr; } return *this;`
C) `*this = std::move(other); return *this;`
D) `data_ = other.data_; return *this;`

---

## Вопрос 26 (Сложный)
Как правильно использовать =delete для запрета операций?

```cpp
class NonCopyable {
    // Как запретить копирование?
};
```

**Варианты ответов:**
A) `NonCopyable(const NonCopyable&) = delete; NonCopyable& operator=(const NonCopyable&) = delete;`
B) Не определять эти функции
C) Определить их как private
D) Использовать только `= default`

---

## Вопрос 27 (Сложный)
Что произойдет при компиляции следующего кода?

```cpp
class Modern {
    std::string str_;
    std::vector<int> vec_;
    std::unique_ptr<Resource> ptr_;
    // Никаких явных определений пяти функций
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
D) Утечка памяти

---

## Вопрос 28 (Сложный)
Как правильно реализовать виртуальный clone для полиморфизма?

```cpp
class Base {
public:
    virtual ~Base() = default;
    virtual Base* clone() const = 0;
};

class Derived : public Base {
    int data_;
public:
    // Как реализовать clone?
};
```

**Варианты ответов:**
A) `Derived* clone() const override { return new Derived(*this); }`
B) `Base* clone() const override { return new Derived(*this); }`
C) `Derived clone() const { return *this; }`
D) Нельзя реализовать clone

---

## Вопрос 29 (Сложный)
Что произойдет при выполнении следующего кода?

```cpp
class Resource {
    int* data_;
public:
    Resource() : data_(new int(42)) {}
    ~Resource() { delete data_; }
    
    Resource(const Resource& other) : data_(new int(*other.data_)) {}
    Resource& operator=(const Resource& other) {
        delete data_;
        data_ = new int(*other.data_);
        return *this;
    }
    // Move операции не определены
};

void func() {
    Resource r1;
    Resource r2;
    r2 = std::move(r1);  // Что здесь?
}
```

**Варианты ответов:**
A) Вызовется оператор присваивания копированием
B) Ошибка компиляции: нет оператора присваивания перемещением
C) Неопределенное поведение
D) Утечка памяти

---

## Вопрос 30 (Сложный)
Как правильно использовать copy-and-swap с move операциями?

```cpp
class Swappable {
    Resource* res_;
public:
    void swap(Swappable& other) noexcept { /* ... */ }
    
    Swappable& operator=(Swappable other) {  // Принимает по значению
        swap(other);
        return *this;
    }
    // Нужен ли отдельный move оператор присваивания?
};
```

**Варианты ответов:**
A) Нужен отдельный `Swappable& operator=(Swappable&&)`
B) Не нужен, copy-and-swap работает для обоих случаев
C) Нужен только для копирования
D) Нужен только для перемещения

---

## Вопрос 31 (Сложный)
Что произойдет при компиляции следующего кода?

```cpp
class Buffer {
    size_t size_;
    char* data_;
public:
    Buffer(Buffer&& other) noexcept
        : size_(other.size_)
        , data_(other.data_)
    {
        other.size_ = 0;
        other.data_ = nullptr;
    }
    
    Buffer& operator=(Buffer&& other) noexcept {
        size_ = other.size_;
        data_ = other.data_;
        other.size_ = 0;
        other.data_ = nullptr;
        return *this;
    }
    // Что не хватает?
};
```

**Варианты ответов:**
A) Код правильный
B) Нужно освободить старую память: `delete[] data_;`
C) Нужно добавить проверку самоприсваивания
D) Нужно добавить `const`

---

## Вопрос 32 (Сложный)
Как правильно реализовать Rule of Five для класса с наследованием?

```cpp
class Base {
    int base_data_;
public:
    virtual ~Base() = default;
    // Что нужно определить?
};

class Derived : public Base {
    int derived_data_;
public:
    // Что нужно определить?
};
```

**Варианты ответов:**
A) В Base и Derived нужно определить все пять функций
B) В Base достаточно деструктора, в Derived - все пять
C) В Base все пять, в Derived только деструктор
D) Достаточно виртуального деструктора в Base

---

## Вопрос 33 (Сложный)
Что произойдет при выполнении следующего кода?

```cpp
class Resource {
    std::unique_ptr<int> data_;
public:
    Resource() : data_(std::make_unique<int>(42)) {}
    ~Resource() = default;
    // Остальные функции не определены
};

void func() {
    Resource r1;
    Resource r2 = r1;  // Что здесь?
}
```

**Варианты ответов:**
A) Код скомпилируется, создастся копия
B) Ошибка компиляции: unique_ptr нельзя копировать
C) Неопределенное поведение
D) Утечка памяти

---

## Вопрос 34 (Сложный)
Как правильно использовать =default для move операций с noexcept?

```cpp
class Safe {
    std::string data_;
public:
    Safe(Safe&& other) noexcept = default;
    Safe& operator=(Safe&& other) noexcept = default;
    // Правильно ли?
};
```

**Варианты ответов:**
A) Да, правильно
B) Нет, нельзя использовать =default с noexcept
C) Нужно явно реализовать функции
D) Нужно добавить const

---

## Вопрос 35 (Сложный)
Что произойдет при компиляции следующего кода?

```cpp
class Complete {
    int* data_;
public:
    Complete() : data_(new int(42)) {}
    ~Complete() { delete data_; }
    
    Complete(const Complete& other) : data_(new int(*other.data_)) {}
    Complete& operator=(const Complete& other) {
        if (this != &other) {
            delete data_;
            data_ = new int(*other.data_);
        }
        return *this;
    }
    
    Complete(Complete&& other) noexcept
        : data_(other.data_)
    {
        other.data_ = nullptr;
    }
    
    Complete& operator=(Complete&& other) noexcept {
        if (this != &other) {
            delete data_;
            data_ = other.data_;
            other.data_ = nullptr;
        }
        return *this;
    }
};
```

**Варианты ответов:**
A) Код правильный, все пять функций определены
B) Нарушение Rule of Five: нужно добавить swap
C) Ошибка компиляции
D) Неопределенное поведение

---

## Правильные ответы

1. **B** - Деструктор, конструктор копирования, оператор присваивания копированием, конструктор перемещения, оператор присваивания перемещением
2. **C** - Все пять функций (деструктор, копирование, перемещение)
3. **B** - Возможны double-delete или утечки памяти
4. **B** - Не нужно определять ни одну из пяти функций, если все члены - RAII-типы
5. **A** - Деструктор, конструктор копирования, оператор присваивания копированием, конструктор перемещения, оператор присваивания перемещением
6. **A** - `noexcept`
7. **B** - Нарушение Rule of Five: нужно определить все пять функций
8. **B** - `size_ = other.size_; data_ = new char[size_]; std::copy(...);` (глубокое копирование)
9. **B** - `if (this != &other) { delete data_; data_ = new int(*other.data_); } return *this;`
10. **A** - `swap(other); return *this;`
11. **B** - `size_ = other.size_; data_ = other.data_; other.data_ = nullptr; other.size_ = 0;`
12. **B** - `if (this != &other) { delete data_; data_ = other.data_; other.data_ = nullptr; } return *this;`
13. **B** - Объект нельзя перемещать, т.к. move операции не определены
14. **A** - `Special(const Special&) = delete; Special& operator=(const Special&) = delete; Special(Special&&) = default; Special& operator=(Special&&) = default;`
15. **A** - Код правильный, деструктор должен быть виртуальным
16. **A** - `~Modern() = default; Modern(const Modern&) = default; Modern& operator=(const Modern&) = default; Modern(Modern&&) noexcept = default; Modern& operator=(Modern&&) noexcept = default;`
17. **B** - Неопределенное поведение: двойное удаление при выходе
18. **B** - `auto temp = std::make_unique<Resource>(*other.res_); res_ = std::move(temp); return *this;`
19. **B** - Нужно добавить `noexcept`
20. **A** - `using std::swap; swap(res_, other.res_);` и пометить `noexcept`
21. **A** - Вызовется конструктор копирования
22. **A** - `Container temp(other); swap(temp); return *this;`
23. **B** - Нужны только деструктор и конструктор копирования
24. **A** - `if (this != &other) { /* ... */ } return *this;`
25. **B** - `if (this != &other) { delete[] data_; size_ = other.size_; data_ = other.data_; other.size_ = 0; other.data_ = nullptr; } return *this;`
26. **A** - `NonCopyable(const NonCopyable&) = delete; NonCopyable& operator=(const NonCopyable&) = delete;`
27. **B** - Ошибка компиляции: unique_ptr нельзя копировать
28. **B** - `Base* clone() const override { return new Derived(*this); }`
29. **A** - Вызовется оператор присваивания копированием
30. **B** - Не нужен, copy-and-swap работает для обоих случаев
31. **B** - Нужно освободить старую память: `delete[] data_;`
32. **A** - В Base и Derived нужно определить все пять функций
33. **B** - Ошибка компиляции: unique_ptr нельзя копировать
34. **A** - Да, правильно
35. **A** - Код правильный, все пять функций определены


