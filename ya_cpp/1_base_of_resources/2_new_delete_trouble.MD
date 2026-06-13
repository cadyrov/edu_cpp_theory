# 2. Проблемы использования new/delete

## Суть

`new/delete` работают, но требуют идеальной дисциплины.

Проблема: между `new` и `delete` может произойти что угодно:

- ранний `return`;
- исключение;
- забытый `delete`;
- несколько ресурсов в одной функции.

Итог: ручной `delete` легко пропустить.

## Пример 1: забыли delete

```cpp
void foo() {
    int* p = new int(42);

    // delete p; забыли
}
```

Проблема: память утекла.

## Пример 2: ранний return

```cpp
void foo(bool error) {
    int* p = new int(42);

    if (error) {
        return;
    }

    delete p;
}
```

Если `error == true`, `delete p` не выполнится.

## Пример 3: исключение

```cpp
void may_throw();

void foo() {
    int* p = new int(42);

    may_throw();

    delete p;
}
```

Если `may_throw()` бросит исключение, `delete p` не выполнится.

## Пример 4: несколько ресурсов

```cpp
void foo() {
    int* a = new int(1);
    int* b = new int(2);

    // сложная логика

    delete b;
    delete a;
}
```

Чем больше ресурсов, тем проще ошибиться.

## Пример 5: double delete

```cpp
void foo() {
    int* p = new int(42);

    delete p;
    delete p; // undefined behavior
}
```

Один объект можно освободить только один раз.

## Пример 6: висячий указатель

```cpp
void foo() {
    int* p = new int(42);

    delete p;

    *p = 100; // undefined behavior
}
```

После `delete` указатель хранит старый адрес, но объект уже уничтожен.

Иногда после `delete` указатель зануляют:

```cpp
delete p;
p = nullptr;
```

Это не чинит архитектуру, но убирает старый опасный адрес из переменной.

## Пример 7: частичная инициализация

```cpp
struct A {};
struct B {};

void foo() {
    A* a = new A();
    B* b = new B(); // если тут исключение, a утечет

    delete b;
    delete a;
}
```

Даже до основной логики можно получить утечку.

Если второй `new` бросит `std::bad_alloc`, до `delete a` выполнение не дойдет.

## Главная проблема

Код освобождения ресурса отделен от кода владения ресурсом.

```cpp
int* p = new int(42);

// много кода

delete p;
```

Нужно помнить, где и когда вызвать `delete`.

## Мост к unique_ptr

`std::unique_ptr` решает эту проблему: освобождает память автоматически.

```cpp
#include <memory>

void may_throw();

void foo() {
    auto p = std::make_unique<int>(42);

    may_throw();
}
```

Если будет исключение, память все равно освободится.

## Саммари

- `new/delete` требуют ручного контроля.
- Ранний `return` может пропустить `delete`.
- Исключение может пропустить `delete`.
- Несколько ресурсов усложняют код.
- Double delete - undefined behavior.
- Использование указателя после `delete` - undefined behavior.
- Несколько `new` подряд опасны из-за частичной инициализации.
- Главная проблема: владение ресурсом и освобождение ресурса разнесены.
- Следующий шаг: `std::unique_ptr`.
