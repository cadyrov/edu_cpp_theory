# Boost.ASIO Strands & Execution Control

## Определение
- `io_context` — ядро event loop: очередь задач, poll/dispatch событий, источники I/O.
- Поток (std::thread) — исполнитель, который вызывает `io_context::run()` и вытаскивает обработчики из очереди.
- `strand` — сериализатор обработчиков, гарантия, что связанные callback-и выполняются без гонок даже в пуле потоков.

## Зачем это нужно
- Масштабировать обработку асинхронных операций на несколько потоков.
- Упростить синхронизацию без явных мьютексов (strand даёт порядок).
- Контролировать немедленный/отложенный запуск обработчиков через `dispatch` / `post` / `defer`.

## `io_context` vs `strand`
- `io_context` управляет жизненным циклом событий и очередями, но не гарантирует порядок при нескольких потоках.
- `strand` — лёгкая прослойка поверх `io_context`, имеет собственную очередь и контролирует сериализацию.
- Один `io_context` может обслуживать несколько `strand`, каждый со своей логикой.
- Без `strand` два обработчика одного объекта могут одновременно работать в разных потоках → гонки.

## Примитивы планирования
- `dispatch(handler)` — если текущий поток уже внутри того же `strand`/`io_context`, обработчик вызовется сразу (in-line), иначе поставится в очередь.
- `post(handler)` — всегда помещает обработчик в очередь соответствующего executor, выполнение гарантированно асинхронно.
- `defer(handler)` — похож на `post`, но позволяет оптимизировать хвостовую рекурсию: если executor поддерживает stackless режим, handler может быть объединён и выполнен после возврата стека.

## Потоки, `strand` и синхронизация
- Типичный паттерн: один `io_context` + пул `std::thread`, каждый вызывает `io_context.run()`.
- Обработчики, завязанные на общий ресурс, связываем с `strand`, создавая через `boost::asio::make_strand(io_context)`.
- Структуры без shared state (например, read-only операции) можно подавать напрямую в `io_context` без `strand`.

```cpp
boost::asio::io_context io;
auto strand = boost::asio::make_strand(io);

boost::asio::steady_timer t1(io, 1s);
boost::asio::steady_timer t2(io, 1s);

auto safe_handler = [](std::string name) {
    std::cout << name << " on thread " << std::this_thread::get_id() << '\n';
};

t1.async_wait(boost::asio::bind_executor(strand, [=](auto){ safe_handler("timer1"); }));
t2.async_wait(boost::asio::bind_executor(strand, [=](auto){ safe_handler("timer2"); }));

std::vector<std::thread> pool;
for (int i = 0; i < 4; ++i)
    pool.emplace_back([&]{ io.run(); });
```

- Через `bind_executor(strand, handler)` оба таймера выполняются по очереди, хоть и работают в пуле из 4 потоков.
- Для независимых операций можно вызвать `post(io, handler)` и позволить им выполняться параллельно.

## Выбор: `dispatch` / `post` / `defer`
- Внутри обработчика `strand` → `dispatch` удобно, когда можно завершить работу сразу без переключения контекста.
- Для очереди фоновых задач → `post`, чтобы точно разнести выполнение.
- Для рекурсивных цепочек колбэков (например, async read loop) → `defer`, чтобы избежать глубокого стека и дать шансу другим handler-ам отработать.

## Примеры

### ✅ Хорошо
- Общий ресурс обновляется только через `strand`, обработчики планируются `post`, чтобы исключить гонки и сохранить порядок.

```cpp
boost::asio::io_context io;
auto strand = boost::asio::make_strand(io);

int shared_state = 0;
boost::asio::steady_timer fast(io, 10ms);
boost::asio::steady_timer slow(io, 20ms);

auto update = [&](std::string_view name) {
    std::cout << name << " before: " << shared_state << '\n';
    ++shared_state;
    std::cout << name << " after: " << shared_state << '\n';
};

fast.async_wait(boost::asio::bind_executor(
    strand,
    [=](const boost::system::error_code&){ boost::asio::dispatch(strand, [=]{ update("fast"); }); }
));

slow.async_wait(boost::asio::bind_executor(
    strand,
    [=](const boost::system::error_code&){ boost::asio::post(strand, [=]{ update("slow"); }); }
));

std::jthread worker([&]{ io.run(); });
```

- Обработчики вызываются последовательно, `shared_state` меняется детерминированно, нет блокировок.

### ❌ Плохо
- Общий ресурс обновляется из нескольких потоков без `strand`, гонки и непредсказуемый порядок.

```cpp
boost::asio::io_context io;
boost::asio::steady_timer fast(io, 10ms);
boost::asio::steady_timer slow(io, 20ms);

int shared_state = 0;

auto update = [&](std::string_view name) {
    std::cout << name << " before: " << shared_state << '\n';
    ++shared_state; // data race с несколькими потоками run()
};

fast.async_wait([=](const boost::system::error_code&){ update("fast"); });
slow.async_wait([=](const boost::system::error_code&){ update("slow"); });

std::jthread t1([&]{ io.run(); });
std::jthread t2([&]{ io.run(); });
```

- При двух потоках `run()` вывод и работа с `shared_state` пересекаются, возможны пропуски, дубли и падения при сложном состоянии.

