# 3. std::shared_ptr в многопоточной среде

## Суть

`std::shared_ptr` можно копировать и уничтожать из разных потоков.

Счетчик владельцев внутри `shared_ptr` потокобезопасен.

Но сам объект, на который указывает `shared_ptr`, потокобезопасным от этого не становится.

```cpp
#include <memory>

int main() {
    auto p = std::make_shared<int>(42);
}
```

`shared_ptr` решает lifetime.

Синхронизацию данных нужно решать отдельно.

## Пример 1: передача shared_ptr в поток

```cpp
#include <iostream>
#include <memory>
#include <thread>

void print(std::shared_ptr<int> p) {
    std::cout << *p << '\n';
}

int main() {
    auto p = std::make_shared<int>(42);

    std::thread t(print, p);
    t.join();
}
```

Вывод:

```text
42
```

Разбор:

```cpp
std::thread t(print, p);
```

В поток передается копия `shared_ptr`.

Объект будет жить минимум до конца функции `print`.

## Пример 2: счетчик безопасен

```cpp
#include <memory>
#include <thread>
#include <vector>

int main() {
    auto p = std::make_shared<int>(42);
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([p] {
            auto local = p;
        });
    }

    for (auto& t : threads) {
        t.join();
    }
}
```

Копии `shared_ptr` создаются в разных потоках.

Счетчик владельцев корректно обновляется.

## Пример 3: данные внутри не защищены

```cpp
#include <memory>
#include <thread>

int main() {
    auto value = std::make_shared<int>(0);

    std::thread t1([value] {
        ++*value;
    });

    std::thread t2([value] {
        ++*value;
    });

    t1.join();
    t2.join();
}
```

Код плохой.

Два потока одновременно меняют один `int`.

Это гонка данных.

`shared_ptr` защитил время жизни объекта, но не защитил сам `int`.

## Пример 4: защита mutex

```cpp
#include <memory>
#include <mutex>
#include <thread>

struct Counter {
    std::mutex mutex;
    int value = 0;
};

int main() {
    auto counter = std::make_shared<Counter>();

    std::thread t1([counter] {
        std::lock_guard lock(counter->mutex);
        ++counter->value;
    });

    std::thread t2([counter] {
        std::lock_guard lock(counter->mutex);
        ++counter->value;
    });

    t1.join();
    t2.join();
}
```

Теперь доступ к `value` защищен.

`shared_ptr` отвечает за lifetime.

`mutex` отвечает за синхронизацию данных.

## Пример 5: атомарная замена shared_ptr

```cpp
#include <atomic>
#include <iostream>
#include <memory>

int main() {
    std::atomic<std::shared_ptr<int>> current;

    current.store(std::make_shared<int>(10));

    auto old_value = current.load();

    current.store(std::make_shared<int>(20));

    std::cout << *old_value << '\n';
    std::cout << *current.load() << '\n';
}
```

Вывод:

```text
10
20
```

`old_value` держит старый объект живым.

`current` уже указывает на новый объект.

## Подводные камни

### shared_ptr не заменяет mutex

Плохо:

```cpp
auto value = std::make_shared<int>(0);

// разные потоки
++*value;
```

Счетчик владельцев защищен.

Сам `int` не защищен.

### Один и тот же shared_ptr нельзя менять без синхронизации

Разные объекты `shared_ptr`, которые владеют одним ресурсом, можно копировать в разных потоках.

Но если несколько потоков меняют одну и ту же переменную `shared_ptr`, нужна синхронизация.

Для этого можно использовать:

- `std::mutex`;
- `std::atomic<std::shared_ptr<T>>`.

### Не держите lock дольше нужного

Если объект большой и читается часто, иногда лучше заменить весь `shared_ptr` на новую immutable-версию.

Так читатели не держат общий mutex во время долгой работы.

## Что будет выведено

```cpp
#include <atomic>
#include <iostream>
#include <memory>

int main() {
    std::atomic<std::shared_ptr<int>> p;

    p.store(std::make_shared<int>(1));

    auto saved = p.load();
    p.store(std::make_shared<int>(2));

    std::cout << *saved << '\n';
    std::cout << *p.load() << '\n';
}
```

Вывод:

```text
1
2
```

## Саммари

- `shared_ptr` можно копировать и уничтожать из разных потоков.
- Счетчик владельцев потокобезопасен.
- Объект внутри `shared_ptr` не становится потокобезопасным.
- Для данных нужны `mutex`, атомики или immutable-подход.
- Копия `shared_ptr` продлевает жизнь объекта в потоке.
- Одну переменную `shared_ptr` нельзя менять из разных потоков без синхронизации.
- Для атомарной замены подходит `std::atomic<std::shared_ptr<T>>`.
