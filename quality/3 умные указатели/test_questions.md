# Тест по умным указателям в C++

## Вопрос 1
Что произойдет при выполнении следующего кода?
```cpp
#include <memory>
#include <iostream>

int main() {
    std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
    std::unique_ptr<int> ptr2 = ptr1;
    std::cout << *ptr2;
}
```
**A)** Выведет 42  
**B)** Ошибка компиляции  
**C)** Неопределенное поведение  
**D)** Исключение во время выполнения  

---

## Вопрос 2
Какой из следующих способов создания `unique_ptr` является предпочтительным?
**A)** `std::unique_ptr<int> ptr(new int(42));`  
**B)** `auto ptr = std::make_unique<int>(42);`  
**C)** `std::unique_ptr<int> ptr = new int(42);`  
**D)** `auto ptr = std::unique_ptr<int>(42);`  

---

## Вопрос 3
Что выведет следующий код?
```cpp
#include <memory>
#include <iostream>

struct Resource {
    Resource() { std::cout << "Created "; }
    ~Resource() { std::cout << "Destroyed "; }
};

int main() {
    auto ptr1 = std::make_unique<Resource>();
    auto ptr2 = std::move(ptr1);
    if (!ptr1) {
        std::cout << "ptr1 is empty ";
    }
    return 0;
}
```
**A)** Created ptr1 is empty Destroyed  
**B)** Created Destroyed ptr1 is empty  
**C)** Created ptr1 is empty  
**D)** ptr1 is empty Created Destroyed  

---

## Вопрос 4
В каком случае следует использовать `shared_ptr` вместо `unique_ptr`?
**A)** Когда объект может быть очень большим  
**B)** Когда несколько объектов должны совместно владеть ресурсом  
**C)** Когда нужна лучшая производительность  
**D)** Когда объект создается в конструкторе  

---

## Вопрос 5
Что произойдет при выполнении данного кода?
```cpp
#include <memory>

int main() {
    int* raw = new int(42);
    std::shared_ptr<int> ptr1(raw);
    std::shared_ptr<int> ptr2(raw);
    return 0;
}
```
**A)** Корректное выполнение  
**B)** Двойное удаление (double delete)  
**C)** Утечка памяти  
**D)** Ошибка компиляции  

---

## Вопрос 6
Какой метод `shared_ptr` возвращает количество владельцев объекта?
**A)** `count()`  
**B)** `use_count()`  
**C)** `ref_count()`  
**D)** `owners()`  

---

## Вопрос 7
Что выведет следующий код?
```cpp
#include <memory>
#include <iostream>

int main() {
    auto ptr1 = std::make_shared<int>(42);
    auto ptr2 = ptr1;
    std::cout << ptr1.use_count() << " ";
    ptr2.reset();
    std::cout << ptr1.use_count();
    return 0;
}
```
**A)** 2 1  
**B)** 1 1  
**C)** 2 0  
**D)** 1 0  

---

## Вопрос 8
Для чего используется `weak_ptr`?
**A)** Для улучшения производительности  
**B)** Для разрыва циклических ссылок  
**C)** Для экономии памяти  
**D)** Для создания объектов в куче  

---

## Вопрос 9
Что произойдет при выполнении этого кода?
```cpp
#include <memory>
#include <iostream>

struct A {
    std::shared_ptr<struct B> b_ptr;
    ~A() { std::cout << "~A "; }
};

struct B {
    std::shared_ptr<A> a_ptr;
    ~B() { std::cout << "~B "; }
};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->b_ptr = b;
    b->a_ptr = a;
    return 0;
}
```
**A)** ~A ~B  
**B)** ~B ~A  
**C)** Ничего не выведет (утечка памяти)  
**D)** Ошибка компиляции  

---

## Вопрос 10
Какой метод `weak_ptr` проверяет, существует ли еще объект?
**A)** `valid()`  
**B)** `expired()`  
**C)** `exists()`  
**D)** `alive()`  

---

## Вопрос 11
Что вернет `weak_ptr::lock()` если объект уже удален?
```cpp
#include <memory>

int main() {
    std::weak_ptr<int> weak;
    {
        auto shared = std::make_shared<int>(42);
        weak = shared;
    }
    auto locked = weak.lock();
    // Что содержит locked?
}
```
**A)** Указатель на объект  
**B)** `nullptr`  
**C)** Исключение  
**D)** Неопределенное поведение  

---

## Вопрос 12
Какая проблема может возникнуть при использовании `get()` у умного указателя?
**A)** Снижение производительности  
**B)** Возможность случайного `delete`  
**C)** Увеличение use_count  
**D)** Автоматическое обнуление указателя  

---

## Вопрос 13
Что выведет этот код?
```cpp
#include <memory>
#include <iostream>

class Widget : public std::enable_shared_from_this<Widget> {
public:
    std::shared_ptr<Widget> getShared() {
        return shared_from_this();
    }
    ~Widget() { std::cout << "~Widget "; }
};

int main() {
    auto w1 = std::make_shared<Widget>();
    auto w2 = w1->getShared();
    std::cout << w1.use_count() << " ";
    return 0;
}
```
**A)** 2 ~Widget  
**B)** 1 ~Widget  
**C)** 2  
**D)** 1  

---

## Вопрос 14
В идиоме Pimpl для чего используется `unique_ptr`?
**A)** Для ускорения компиляции  
**B)** Для автоматического управления памятью impl-структуры  
**C)** Для сокрытия зависимостей  
**D)** Все вышеперечисленное  

---

## Вопрос 15
Что нужно явно объявить в классе, использующем идиому Pimpl?
```cpp
class MyClass {
public:
    MyClass();
    // Что еще нужно объявить?
private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
```
**A)** Только деструктор  
**B)** Деструктор и конструктор перемещения  
**C)** Деструктор, конструктор перемещения и оператор присваивания  
**D)** Ничего дополнительного  

---

## Вопрос 16
Какое преимущество дает `make_shared` по сравнению с `shared_ptr(new T())`?
**A)** Лучшая производительность  
**B)** Безопасность исключений  
**C)** Одно выделение памяти вместо двух  
**D)** Все вышеперечисленное  

---

## Вопрос 17
Что произойдет при выполнении кода?
```cpp
#include <memory>
#include <vector>

void process(const std::vector<int>& vec) {
    // some processing
}

int main() {
    auto ptr = std::make_shared<std::vector<int>>(1000, 42);
    process(*ptr);
    return 0;
}
```
**A)** Копирование вектора  
**B)** Перемещение вектора  
**C)** Передача по ссылке (без копирования)  
**D)** Ошибка компиляции  

---

## Вопрос 18
В Copy-on-Write когда происходит фактическое копирование данных?
**A)** При создании копии объекта  
**B)** При первом обращении к данным  
**C)** При попытке модификации, если use_count > 1  
**D)** При разрушении объекта  

---

## Вопрос 19
Что выведет следующий код?
```cpp
#include <memory>
#include <iostream>

int main() {
    std::unique_ptr<int> ptr;
    if (!ptr) {
        std::cout << "empty ";
    }
    ptr = std::make_unique<int>(42);
    if (ptr) {
        std::cout << "not empty ";
    }
    return 0;
}
```
**A)** empty  
**B)** not empty  
**C)** empty not empty  
**D)** Ошибка компиляции  

---

## Вопрос 20
Какой из умных указателей является move-only типом?
**A)** `shared_ptr`  
**B)** `weak_ptr`  
**C)** `unique_ptr`  
**D)** Все вышеперечисленные  

---

## Вопрос 21
Что произойдет при выполнении кода?
```cpp
#include <memory>

std::unique_ptr<int> factory() {
    return std::make_unique<int>(42);
}

int main() {
    auto ptr1 = factory();
    auto ptr2 = factory();
    auto ptr3 = std::move(ptr1);
    return 0;
}
```
**A)** Создастся 3 объекта в памяти  
**B)** Создастся 2 объекта в памяти  
**C)** Ошибка компиляции  
**D)** Утечка памяти  

---

## Вопрос 22
Какой метод `shared_ptr` позволяет обнулить указатель?
**A)** `clear()`  
**B)** `reset()`  
**C)** `release()`  
**D)** `null()`  

---

## Вопрос 23
Что выведет код?
```cpp
#include <memory>
#include <iostream>

int main() {
    auto shared = std::make_shared<int>(42);
    std::weak_ptr<int> weak = shared;
    
    shared.reset();
    
    if (weak.expired()) {
        std::cout << "expired";
    } else {
        std::cout << "valid";
    }
    return 0;
}
```
**A)** expired  
**B)** valid  
**C)** Ошибка компиляции  
**D)** Неопределенное поведение  

---

## Вопрос 24
Какая из функций не является членом `unique_ptr`?
**A)** `get()`  
**B)** `release()`  
**C)** `reset()`  
**D)** `use_count()`  

---

## Вопрос 25
Что произойдет при попытке скопировать `unique_ptr`?
```cpp
#include <memory>

int main() {
    auto ptr1 = std::make_unique<int>(42);
    auto ptr2 = ptr1; // Что произойдет здесь?
    return 0;
}
```
**A)** Создастся копия объекта  
**B)** Ошибка компиляции  
**C)** ptr1 станет nullptr  
**D)** Неопределенное поведение  

---

## Вопрос 26
В каком случае полезна оптимизация Copy-on-Write?
**A)** Когда объекты часто копируются, но редко изменяются  
**B)** Когда объекты часто изменяются  
**C)** Когда объекты малого размера  
**D)** Когда нужна максимальная скорость  

---

## Вопрос 27
Что выведет код?
```cpp
#include <memory>
#include <iostream>

struct Base {
    virtual ~Base() { std::cout << "~Base "; }
};

struct Derived : Base {
    ~Derived() { std::cout << "~Derived "; }
};

int main() {
    std::unique_ptr<Base> ptr = std::make_unique<Derived>();
    return 0;
}
```
**A)** ~Base  
**B)** ~Derived  
**C)** ~Derived ~Base  
**D)** Ничего  

---

## Вопрос 28
Какой заголовочный файл нужно подключить для использования умных указателей?
**A)** `<smart_ptr>`  
**B)** `<memory>`  
**C)** `<unique_ptr>`  
**D)** `<pointers>`  

---

## Вопрос 29
Что произойдет при выполнении кода?
```cpp
#include <memory>

void func(std::shared_ptr<int> ptr) {
    // function body
}

int main() {
    auto ptr = std::make_shared<int>(42);
    func(ptr);
    // Сколько владельцев у объекта после возврата из func?
    return 0;
}
```
**A)** 0  
**B)** 1  
**C)** 2  
**D)** Неопределенно  

---

## Вопрос 30
Какая операция недоступна для `weak_ptr`?
**A)** `lock()`  
**B)** `expired()`  
**C)** Оператор `*`  
**D)** `reset()`  

---

## Вопрос 31
Что выведет следующий код?
```cpp
#include <memory>
#include <iostream>

int main() {
    std::shared_ptr<int> ptr1;
    std::shared_ptr<int> ptr2 = std::make_shared<int>(42);
    
    ptr1 = ptr2;
    
    std::cout << ptr2.use_count();
    return 0;
}
```
**A)** 1  
**B)** 2  
**C)** 0  
**D)** Неопределенно  

---

## Вопрос 32
Какой deleter используется по умолчанию в `unique_ptr` и `shared_ptr`?
**A)** `free`  
**B)** `delete`  
**C)** `delete[]`  
**D)** Пользовательский  

---

## Вопрос 33
Что произойдет при выполнении кода?
```cpp
#include <memory>

int main() {
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(10);
    arr[0] = 42;
    // Как будет удален массив?
    return 0;
}
```
**A)** Через `delete`  
**B)** Через `delete[]`  
**C)** Через `free`  
**D)** Не будет удален  

---

## Вопрос 34
В идиоме Pimpl где должен быть определен деструктор?
**A)** В заголовочном файле (.h)  
**B)** В файле реализации (.cpp)  
**C)** В обоих файлах  
**D)** Не важно где  

---

## Вопрос 35
Что выведет код?
```cpp
#include <memory>
#include <iostream>

int main() {
    auto ptr = std::shared_ptr<int>(new int(42));
    std::cout << *ptr << " ";
    
    auto ptr2 = std::shared_ptr<int>(ptr.get());
    std::cout << *ptr2;
    
    return 0;
}
```
**A)** 42 42  
**B)** Неопределенное поведение  
**C)** Ошибка компиляции  
**D)** 42 и затем исключение  

---

## Вопрос 36
Какой тип возвращает `unique_ptr::release()`?
**A)** `void`  
**B)** Сырой указатель  
**C)** `unique_ptr`  
**D)** `bool`  

---

## Вопрос 37
Что происходит с объектом при вызове `shared_ptr::reset()`?
**A)** Объект всегда удаляется  
**B)** Объект удаляется, если это последняя ссылка  
**C)** Объект никогда не удаляется  
**D)** Зависит от типа объекта  

---

## Вопрос 38
Что выведет код?
```cpp
#include <memory>
#include <iostream>

int main() {
    auto ptr1 = std::make_shared<int>(42);
    std::weak_ptr<int> weak = ptr1;
    
    ptr1.reset();
    auto ptr2 = weak.lock();
    
    if (ptr2) {
        std::cout << "valid";
    } else {
        std::cout << "invalid";
    }
    return 0;
}
```
**A)** valid  
**B)** invalid  
**C)** Ошибка компиляции  
**D)** Исключение  

---

## Вопрос 39
Какое главное преимущество `auto_ptr` было устранено в `unique_ptr`?
**A)** Невозможность копирования  
**B)** Опасное поведение при копировании  
**C)** Отсутствие перемещающей семантики  
**D)** Все вышеперечисленное  

---

## Вопрос 40
Что произойдет при выполнении этого кода?
```cpp
#include <memory>
#include <iostream>

class Resource {
public:
    Resource() { std::cout << "Created "; }
    ~Resource() { std::cout << "Destroyed "; }
    void use() { std::cout << "Used "; }
};

int main() {
    std::shared_ptr<Resource> ptr1;
    {
        ptr1 = std::make_shared<Resource>();
        ptr1->use();
    }
    ptr1->use();
    return 0;
}
```
**A)** Created Used Used Destroyed  
**B)** Created Used Destroyed Used  
**C)** Created Used Used  
**D)** Ошибка компиляции 