# Тест по теме: Умные указатели (Smart Pointers) в C++

**Всего вопросов: 35** (от простого к сложному)

## Вопрос 1 (Простой)
Что такое умные указатели (smart pointers)?

```cpp
std::unique_ptr<int> ptr(new int(42));
```

**Варианты ответов:**
A) Указатели, которые автоматически увеличивают значение
B) Классы-обёртки над сырыми указателями, реализующие RAII для автоматического управления памятью
C) Указатели, которые нельзя изменять
D) Указатели, которые работают только с константами

---

## Вопрос 2 (Простой)
Какой умный указатель используется для эксклюзивного владения ресурсом?

```cpp
// Какой указатель гарантирует единоличное владение?
```

**Варианты ответов:**
A) `std::shared_ptr`
B) `std::unique_ptr`
C) `std::weak_ptr`
D) `std::auto_ptr`

---

## Вопрос 3 (Простой)
Что произойдет с памятью при выходе из области видимости unique_ptr?

```cpp
void func() {
    std::unique_ptr<int> ptr(new int(42));
    // Что произойдет с памятью?
}
```

**Варианты ответов:**
A) Память останется выделенной
B) Память автоматически освободится в деструкторе
C) Память нужно освободить вручную
D) Неопределенное поведение

---

## Вопрос 4 (Простой)
Как правильно создать unique_ptr?

```cpp
// Какой вариант предпочтительнее?
```

**Варианты ответов:**
A) `std::unique_ptr<int> ptr(new int(42));`
B) `auto ptr = std::make_unique<int>(42);`
C) `std::unique_ptr<int> ptr = new int(42);`
D) Оба варианта A и B одинаково хороши

---

## Вопрос 5 (Средний)
Что произойдет при компиляции следующего кода?

```cpp
std::unique_ptr<int> ptr1(new int(42));
std::unique_ptr<int> ptr2 = ptr1;  // Что здесь?
```

**Варианты ответов:**
A) Код скомпилируется, создастся копия указателя
B) Ошибка компиляции: unique_ptr нельзя копировать
C) Предупреждение компилятора
D) Неопределенное поведение

---

## Вопрос 6 (Средний)
Как правильно передать владение unique_ptr?

```cpp
std::unique_ptr<int> ptr1(new int(42));
// Как передать владение в ptr2?
```

**Варианты ответов:**
A) `std::unique_ptr<int> ptr2 = ptr1;`
B) `std::unique_ptr<int> ptr2 = std::move(ptr1);`
C) `std::unique_ptr<int> ptr2(ptr1.get());`
D) `std::unique_ptr<int> ptr2 = ptr1.get();`

---

## Вопрос 7 (Средний)
Что такое shared_ptr?

```cpp
std::shared_ptr<int> ptr1(new int(42));
std::shared_ptr<int> ptr2 = ptr1;  // Что здесь?
```

**Варианты ответов:**
A) Указатель для эксклюзивного владения
B) Указатель для разделяемого владения с подсчетом ссылок
C) Указатель, который нельзя копировать
D) Указатель только для чтения

---

## Вопрос 8 (Средний)
Когда память освобождается при использовании shared_ptr?

```cpp
std::shared_ptr<int> ptr1(new int(42));
{
    std::shared_ptr<int> ptr2 = ptr1;
    // Что с памятью при выходе из блока?
}
// Что с памятью здесь?
```

**Варианты ответов:**
A) Память освободится при выходе из блока
B) Память освободится только когда все shared_ptr уничтожены
C) Память никогда не освободится
D) Неопределенное поведение

---

## Вопрос 9 (Средний)
Что произойдет при компиляции следующего кода?

```cpp
std::unique_ptr<int> ptr(new int(42));
delete ptr.get();  // Правильно ли?
```

**Варианты ответов:**
A) Код правильный
B) Ошибка: нельзя вручную удалять память, управляемую unique_ptr
C) Предупреждение компилятора
D) Неопределенное поведение: двойное удаление

---

## Вопрос 10 (Средний)
Как правильно создать shared_ptr?

```cpp
// Какой вариант предпочтительнее?
```

**Варианты ответов:**
A) `std::shared_ptr<int> ptr(new int(42));`
B) `auto ptr = std::make_shared<int>(42);`
C) `std::shared_ptr<int> ptr = new int(42);`
D) Оба варианта A и B одинаково хороши

---

## Вопрос 11 (Средний)
Что такое weak_ptr?

```cpp
std::shared_ptr<int> shared(new int(42));
std::weak_ptr<int> weak = shared;  // Что здесь?
```

**Варианты ответов:**
A) Указатель для эксклюзивного владения
B) Слабая ссылка, не увеличивающая счетчик ссылок shared_ptr
C) Указатель, который нельзя использовать
D) То же самое, что shared_ptr

---

## Вопрос 12 (Средний)
Как получить shared_ptr из weak_ptr?

```cpp
std::weak_ptr<int> weak = /* ... */;
// Как получить shared_ptr?
```

**Варианты ответов:**
A) `std::shared_ptr<int> shared = weak;`
B) `std::shared_ptr<int> shared = weak.lock();`
C) `std::shared_ptr<int> shared = *weak;`
D) Нельзя получить shared_ptr из weak_ptr

---

## Вопрос 13 (Средний)
Для чего используется weak_ptr?

```cpp
struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;  // Зачем weak_ptr?
};
```

**Варианты ответов:**
A) Для увеличения производительности
B) Для предотвращения циклических ссылок
C) Для эксклюзивного владения
D) Для автоматического освобождения памяти

---

## Вопрос 14 (Средний)
Что произойдет при компиляции следующего кода?

```cpp
std::unique_ptr<Base> base = std::make_unique<Derived>();
// Правильно ли?
```

**Варианты ответов:**
A) Ошибка компиляции: нельзя преобразовать типы
B) Код правильный, работает полиморфизм
C) Предупреждение компилятора
D) Неопределенное поведение

---

## Вопрос 15 (Средний)
Как правильно использовать unique_ptr для массивов?

```cpp
// Как создать unique_ptr для массива из 100 элементов?
```

**Варианты ответов:**
A) `std::unique_ptr<int> ptr(new int[100]);`
B) `auto ptr = std::make_unique<int[]>(100);`
C) `std::unique_ptr<int[]> ptr(new int[100]);`
D) Нельзя использовать unique_ptr для массивов

---

## Вопрос 16 (Сложный)
Что произойдет при выполнении следующего кода?

```cpp
void wrong(Resource* res) {
    std::unique_ptr<Resource> ptr(res);
    // res может быть удалён где-то ещё
}

int main() {
    Resource* raw = new Resource();
    wrong(raw);
    delete raw;  // Что здесь?
}
```

**Варианты ответов:**
A) Код правильный
B) Неопределенное поведение: двойное удаление
C) Утечка памяти
D) Ошибка компиляции

---

## Вопрос 17 (Сложный)
Как правильно преобразовать unique_ptr в shared_ptr?

```cpp
std::unique_ptr<int> u = std::make_unique<int>(42);
// Как создать shared_ptr из unique_ptr?
```

**Варианты ответов:**
A) `std::shared_ptr<int> s = u;`
B) `std::shared_ptr<int> s = std::move(u);`
C) `std::shared_ptr<int> s(u.get());`
D) Нельзя преобразовать unique_ptr в shared_ptr

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
struct Node {
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;  // Циклическая ссылка
};

void func() {
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();
    node1->next = node2;
    node2->prev = node1;
    // Что с памятью при выходе?
}
```

**Варианты ответов:**
A) Память автоматически освободится
B) Утечка памяти из-за циклической ссылки
C) Ошибка компиляции
D) Неопределенное поведение

---

## Вопрос 20 (Сложный)
Как правильно исправить циклическую ссылку?

```cpp
struct Node {
    std::shared_ptr<Node> next;
    // Как объявить prev, чтобы избежать циклической ссылки?
};
```

**Варианты ответов:**
A) `std::shared_ptr<Node> prev;`
B) `std::weak_ptr<Node> prev;`
C) `std::unique_ptr<Node> prev;`
D) `Node* prev;`

---

## Вопрос 21 (Сложный)
Что произойдет при компиляции следующего кода?

```cpp
class Resource {
public:
    std::shared_ptr<Resource> getPtr() {
        return std::shared_ptr<Resource>(this);  // Правильно ли?
    }
};

void func() {
    auto res = std::make_shared<Resource>();
    auto ptr = res->getPtr();  // Что здесь?
}
```

**Варианты ответов:**
A) Код правильный
B) Неопределенное поведение: двойное удаление
C) Ошибка компиляции
D) Утечка памяти

---

## Вопрос 22 (Сложный)
Как правильно использовать enable_shared_from_this?

```cpp
class Resource : public std::enable_shared_from_this<Resource> {
public:
    std::shared_ptr<Resource> getPtr() {
        // Что здесь?
    }
};
```

**Варианты ответов:**
A) `return std::shared_ptr<Resource>(this);`
B) `return shared_from_this();`
C) `return std::make_shared<Resource>(*this);`
D) `return this;`

---

## Вопрос 23 (Сложный)
Что произойдет при выполнении следующего кода?

```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
std::shared_ptr<int> ptr2 = ptr1;
std::weak_ptr<int> weak = ptr1;

ptr1.reset();
ptr2.reset();
// Что с weak?
```

**Варианты ответов:**
A) weak все еще валиден
B) weak.expired() вернет true
C) weak можно использовать как shared_ptr
D) Ошибка компиляции

---

## Вопрос 24 (Сложный)
Какой overhead имеет shared_ptr по сравнению с unique_ptr?

```cpp
// Что хранит shared_ptr дополнительно?
```

**Варианты ответов:**
A) Никакого overhead
B) Счетчик ссылок и control block
C) Дополнительный указатель на функцию удаления
D) Дополнительный флаг владения

---

## Вопрос 25 (Сложный)
Что произойдет при компиляции следующего кода?

```cpp
std::unique_ptr<int> create() {
    int* raw = new int(42);
    return std::unique_ptr<int>(raw);
}

void func() {
    auto ptr = create();
    // Что с памятью?
}
```

**Варианты ответов:**
A) Утечка памяти
B) Память автоматически освободится
C) Ошибка компиляции
D) Неопределенное поведение

---

## Вопрос 26 (Сложный)
Как правильно проверить, истек ли weak_ptr?

```cpp
std::weak_ptr<int> weak = /* ... */;
// Как проверить, что объект еще существует?
```

**Варианты ответов:**
A) `if (weak) { /* ... */ }`
B) `if (!weak.expired()) { /* ... */ }`
C) `if (weak.use_count() > 0) { /* ... */ }`
D) Нельзя проверить

---

## Вопрос 27 (Сложный)
Что произойдет при выполнении следующего кода?

```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
std::shared_ptr<int> ptr2(ptr1.get());  // Что здесь?
```

**Варианты ответов:**
A) Код правильный, создастся второй shared_ptr
B) Неопределенное поведение: двойное удаление
C) Ошибка компиляции
D) Утечка памяти

---

## Вопрос 28 (Сложный)
Как правильно использовать unique_ptr с полиморфизмом?

```cpp
class Base {
public:
    virtual ~Base() = default;
};

class Derived : public Base {};

std::unique_ptr<Base> create() {
    // Как правильно вернуть unique_ptr<Derived>?
}
```

**Варианты ответов:**
A) `return std::make_unique<Derived>();`
B) `return std::unique_ptr<Base>(new Derived());`
C) Оба варианта правильные
D) Нельзя использовать полиморфизм с unique_ptr

---

## Вопрос 29 (Сложный)
Что произойдет при компиляции следующего кода?

```cpp
std::unique_ptr<int[]> arr = std::make_unique<int[]>(100);
delete[] arr.get();  // Правильно ли?
```

**Варианты ответов:**
A) Код правильный
B) Ошибка: нельзя вручную удалять память, управляемую unique_ptr
C) Предупреждение компилятора
D) Неопределенное поведение: двойное удаление

---

## Вопрос 30 (Сложный)
Как правильно использовать shared_ptr для массива?

```cpp
// Как создать shared_ptr для массива?
```

**Варианты ответов:**
A) `std::shared_ptr<int> arr(new int[100], std::default_delete<int[]>());`
B) `auto arr = std::make_shared<int[]>(100);`
C) `std::shared_ptr<int[]> arr(new int[100]);`
D) Нельзя использовать shared_ptr для массивов, нужно использовать vector

---

## Вопрос 31 (Сложный)
Что произойдет при выполнении следующего кода?

```cpp
class Resource {
public:
    ~Resource() { std::cout << "Destroyed\n"; }
};

void func() {
    std::shared_ptr<Resource> ptr1 = std::make_shared<Resource>();
    std::weak_ptr<Resource> weak = ptr1;
    ptr1.reset();
    // Что выведется?
}
```

**Варианты ответов:**
A) "Destroyed" (объект уничтожен)
B) Ничего (объект не уничтожен, т.к. weak_ptr держит ссылку)
C) Ошибка компиляции
D) Неопределенное поведение

---

## Вопрос 32 (Сложный)
Как правильно использовать make_shared для класса с приватным конструктором?

```cpp
class Resource {
    Resource() {}  // Приватный конструктор
public:
    static std::shared_ptr<Resource> create() {
        // Как создать shared_ptr?
    }
};
```

**Варианты ответов:**
A) `return std::make_shared<Resource>();`
B) `return std::shared_ptr<Resource>(new Resource());`
C) Оба варианта правильные
D) Нельзя создать shared_ptr для класса с приватным конструктором

---

## Вопрос 33 (Сложный)
Что произойдет при компиляции следующего кода?

```cpp
std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
std::unique_ptr<int> ptr2;
ptr2 = ptr1;  // Что здесь?
```

**Варианты ответов:**
A) Код скомпилируется, создастся копия
B) Ошибка компиляции: нельзя присваивать unique_ptr
C) `ptr2 = std::move(ptr1);` - правильный вариант
D) Предупреждение компилятора

---

## Вопрос 34 (Сложный)
Как правильно использовать shared_ptr с кастомным делитером?

```cpp
auto deleter = [](int* p) { delete[] p; };
// Как создать shared_ptr с кастомным делитером?
```

**Варианты ответов:**
A) `std::shared_ptr<int> ptr(new int[100], deleter);`
B) `auto ptr = std::make_shared<int[]>(100);`
C) `std::shared_ptr<int[]> ptr(new int[100]);`
D) Нельзя использовать кастомный делитер с shared_ptr

---

## Вопрос 35 (Сложный)
Что произойдет при выполнении следующего кода?

```cpp
class Base {
public:
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    ~Derived() { std::cout << "Derived destroyed\n"; }
};

void func() {
    std::unique_ptr<Base> ptr = std::make_unique<Derived>();
    // Что выведется при выходе?
}
```

**Варианты ответов:**
A) "Derived destroyed" (правильный полиморфизм)
B) Ничего (деструктор Base не виртуальный)
C) Ошибка компиляции
D) Неопределенное поведение

---

## Правильные ответы

1. **B** - Классы-обёртки над сырыми указателями, реализующие RAII для автоматического управления памятью
2. **B** - `std::unique_ptr`
3. **B** - Память автоматически освободится в деструкторе
4. **B** - `auto ptr = std::make_unique<int>(42);`
5. **B** - Ошибка компиляции: unique_ptr нельзя копировать
6. **B** - `std::unique_ptr<int> ptr2 = std::move(ptr1);`
7. **B** - Указатель для разделяемого владения с подсчетом ссылок
8. **B** - Память освободится только когда все shared_ptr уничтожены
9. **D** - Неопределенное поведение: двойное удаление
10. **B** - `auto ptr = std::make_shared<int>(42);`
11. **B** - Слабая ссылка, не увеличивающая счетчик ссылок shared_ptr
12. **B** - `std::shared_ptr<int> shared = weak.lock();`
13. **B** - Для предотвращения циклических ссылок
14. **B** - Код правильный, работает полиморфизм
15. **B** - `auto ptr = std::make_unique<int[]>(100);`
16. **B** - Неопределенное поведение: двойное удаление
17. **B** - `std::shared_ptr<int> s = std::move(u);`
18. **B** - `std::unique_ptr<FILE, decltype(deleter)> file(fopen("data.txt", "r"), deleter);`
19. **B** - Утечка памяти из-за циклической ссылки
20. **B** - `std::weak_ptr<Node> prev;`
21. **B** - Неопределенное поведение: двойное удаление
22. **B** - `return shared_from_this();`
23. **B** - weak.expired() вернет true
24. **B** - Счетчик ссылок и control block
25. **B** - Память автоматически освободится
26. **B** - `if (!weak.expired()) { /* ... */ }`
27. **B** - Неопределенное поведение: двойное удаление
28. **C** - Оба варианта правильные
29. **D** - Неопределенное поведение: двойное удаление
30. **A** - `std::shared_ptr<int> arr(new int[100], std::default_delete<int[]>());`
31. **A** - "Destroyed" (объект уничтожен)
32. **B** - `return std::shared_ptr<Resource>(new Resource());`
33. **C** - `ptr2 = std::move(ptr1);` - правильный вариант
34. **A** - `std::shared_ptr<int> ptr(new int[100], deleter);`
35. **A** - "Derived destroyed" (правильный полиморфизм)







