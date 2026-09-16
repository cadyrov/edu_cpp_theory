# 12. Слабые порядки и барьеры памяти

## Суть

Порядок памяти задаёт гарантии атомарной операции относительно других обращений к памяти. Ослабление порядка сохраняет атомарность, но может убрать необходимую синхронизацию.

| Порядок | Назначение |
| --- | --- |
| `relaxed` | Атомарность и согласованность изменений одного атомика, без самостоятельной публикации других данных |
| `release` | Публикация предшествующих действий через запись |
| `acquire` | Получение опубликованных данных через соответствующее чтение |
| `acq_rel` | Приём и публикация в одной RMW-операции |
| `seq_cst` | Порядок по умолчанию: соответствующая acquire/release-семантика и дополнительные гарантии общего порядка seq_cst-операций |

`consume` связан с зависимостями по данным; в примерах этого курса используем `acquire`.

## Примеры

### Release/acquire: одноразовая публикация

```cpp
#include <atomic>
#include <string>

std::string data;
std::atomic<bool> ready{false};

void Producer() {
    data = "готово";
    ready.store(true, std::memory_order_release);
}

void Consumer() {
    if (ready.load(std::memory_order_acquire)) {
        auto copy = data;
    }
}
```

Если acquire-чтение получило `true` от release-записи, возникает synchronizes-with, а запись строки happens-before её чтения. Условия: один производитель, данные живут достаточно долго и после публикации не изменяются.

### Relaxed: независимый счётчик

```cpp
std::atomic<unsigned> calls{0};

void CountCall() {
    calls.fetch_add(1, std::memory_order_relaxed);
}
```

Счётчик не публикует другие данные; прибавления не теряются, пока учитывается переполнение. После `join()` всех работников можно прочитать итог через `load(relaxed)`: нужное ожидание завершения уже обеспечил `join()`.

### Порядки для спинлока

```cpp
class Spinlock {
    std::atomic<bool> locked_{false};
public:
    void lock() noexcept {
        while (locked_.exchange(true, std::memory_order_acquire)) {}
    }
    bool try_lock() noexcept {
        return !locked_.exchange(true, std::memory_order_acquire);
    }
    void unlock() noexcept {
        locked_.store(false, std::memory_order_release);
    }
};
```

Для захвата достаточно `acquire`, хотя `exchange` является RMW. `acq_rel` нужен, когда одна операция должна и принять данные, и опубликовать предшествующие действия; сам факт RMW не делает его обязательным.

### Явные барьеры через `atomic_thread_fence`

Альтернатива первому примеру: оставляем атомарные операции relaxed, а синхронизацию задаём барьерами.

```cpp
void ProducerWithFence() {
    data = "готово";
    std::atomic_thread_fence(std::memory_order_release);
    ready.store(true, std::memory_order_relaxed);
}

void ConsumerWithFence() {
    if (ready.load(std::memory_order_relaxed)) {
        std::atomic_thread_fence(std::memory_order_acquire);
        auto copy = data;
    }
}
```

Release-барьер предшествует записи флага, чтение этой записи предшествует acquire-барьеру. Через эту связь барьеры синхронизируются. Используй эту пару **вместо**, а не одновременно с первой парой производителей и потребителей.

### Release sequence: передача публикации через RMW

В C++20 release sequence — release-операция и непрерывная цепочка следующих за ней RMW в порядке изменений того же атомика. Даже relaxed-RMW может передать первоначальную публикацию acquire-читателю; обычный `store` разрывает эту цепочку. [Определение C++20](https://timsong-cpp.github.io/cppwp/n4861/intro.races#5).

```cpp
int data = 0;
std::atomic<int> stage{0};

// Поток A:
data = 42;
stage.store(1, std::memory_order_release);

// Поток B: переводим именно 1 в 2
int expected = 1;
while (!stage.compare_exchange_weak(expected, 2,
        std::memory_order_relaxed, std::memory_order_relaxed)) {
    expected = 1;
}

// Поток C:
while (stage.load(std::memory_order_acquire) != 2) {}
int result = data; // 42
```

Это одноразовый протокол без других записей. Поток B не читает `data`: его relaxed-CAS сам не получает права на такое чтение. Acquire в C связывается с первоначальной release-записью A.

### Два порядка CAS

В `compare_exchange_weak(expected, desired, success, failure)` успех — RMW, неудача — чтение с обновлением `expected`. Например, для захвата замка подходит пара `acquire, relaxed`, а для публикации нового готового узла — `release, relaxed`, если старые данные не читаются. Если после неудачи разыменовывается полученный указатель, может понадобиться acquire-семантика и отдельная защита времени жизни.

У перегрузки с одним порядком failure-порядок выводится: `acq_rel` → `acquire`, `release` → `relaxed`, иначе остаётся тот же. [Контракт CAS](https://eel.is/c++draft/atomics.types.operations).

## Подводные камни

- Для `load` допустимы `relaxed`, `consume`, `acquire`, `seq_cst`; для `store` — `relaxed`, `release`, `seq_cst`. `acq_rel` предназначен для RMW, а не обычного чтения или записи.
- Для CAS отдельно учитывай успех и неудачу: при неудаче выполняется чтение, поэтому порядок не может быть `release` или `acq_rel`.
- Acquire/release связываются через чтение соответствующей публикации (или её release sequence), а не просто потому, что обе операции есть в программе.
- `relaxed` не означает «разрешено всё»: сохраняются атомарность, modification order и требования когерентности. Сам по себе он не создаёт synchronizes-with, но может участвовать в протоколе с барьерами.
- Барьеры без подходящей связи через атомарные операции не делают гонку обычных данных корректной. `atomic_thread_fence(relaxed)` ничего не делает.
- Названия LoadLoad, LoadStore, StoreStore и StoreLoad описывают аппаратные ограничения порядка. Это полезная иллюстрация, но доказательство корректности C++ строится через отношения модели памяти.
- `seq_cst` не означает аппаратный полный барьер на каждой операции, а StoreLoad не требует буквально «синхронизировать все кеши». Машинная реализация зависит от архитектуры.
- Более слабый порядок не гарантирует ускорения: инструкции могут совпасть, а конкуренция за линию кеша остаться. Начинай с корректного протокола, затем измеряй.
- `lock()` имеет acquire-семантику, но одного `load(acquire)` недостаточно для захвата: нужно ещё обеспечить взаимное исключение. Освобождение синхронизируется с последующим успешным захватом того же мьютекса.
- `condition_variable` предоставляет протокол ожидания и пробуждения; обычные данные защищает связанный мьютекс. Запуск потока и успешный `join()` тоже создают связи синхронизации.

## Саммари

Для независимого атомарного значения часто достаточно `relaxed`; для публикации данных — release/acquire с доказанной связью чтения и записи. Явные fence нужны для специальных протоколов и не заменяют атомарный канал связи.
