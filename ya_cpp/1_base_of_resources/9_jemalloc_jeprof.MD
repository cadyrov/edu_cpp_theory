# 9. jemalloc и jeprof

## Суть

`jemalloc` - аллокатор памяти.

Аллокатор - это код, который реально выделяет и освобождает память под `malloc`, `free`, `operator new` и `operator delete`.

`jeprof` - утилита для анализа heap profile от `jemalloc`.

Она помогает ответить на вопросы:

- где программа чаще всего выделяет память;
- какие места держат больше всего памяти;
- какие цепочки вызовов приводят к аллокациям.

Важно: `jeprof` работает не с любым профилем, а с профилем, который записал `jemalloc`.

## Зачем это в теме ресурсов

В C++ утечка или лишняя аллокация часто видна не там, где она появилась.

Например:

```cpp
void load_users() {
    std::vector<std::string> users;

    for (int i = 0; i < 1'000'000; ++i) {
        users.push_back(std::to_string(i));
    }
}
```

В коде нет явного `new`, но память выделяется:

- внутри `std::vector`;
- внутри `std::string`;
- внутри стандартной библиотеки.

Профилировщик показывает, какие вызовы реально привели к выделению памяти.

## Установка

На macOS:

```bash
brew install jemalloc
```

На Ubuntu:

```bash
sudo apt install libjemalloc-dev
```

После установки обычно доступны:

```bash
jemalloc-config
jeprof
```

## Сборка программы

Пример программы:

```cpp
#include <string>
#include <vector>

void work() {
    std::vector<std::string> data;

    for (int i = 0; i < 100000; ++i) {
        data.push_back(std::string(100, 'x'));
    }
}

int main() {
    work();
}
```

Собирать лучше с debug symbols:

```bash
c++ -std=c++17 -g -O2 -fno-omit-frame-pointer main.cpp -ljemalloc -o app
```

Зачем:

- `-g` добавляет имена функций и строки;
- `-fno-omit-frame-pointer` помогает строить stack traces;
- `-ljemalloc` подключает `jemalloc`.

## Проверка, что программа использует jemalloc

Linux:

```bash
ldd ./app
```

В выводе должна быть библиотека `jemalloc`.

macOS:

```bash
otool -L ./app
```

В выводе должна быть библиотека `jemalloc`.

## Запуск с heap profiling

Профилирование включается через `MALLOC_CONF`.

```bash
MALLOC_CONF="prof:true,prof_active:true,lg_prof_sample:17,prof_prefix:jeprof.out,prof_final:true" ./app
```

Смысл опций:

- `prof:true` включает heap profiling;
- `prof_active:true` сразу активирует сбор данных;
- `lg_prof_sample:17` задает частоту sampling;
- `prof_prefix:jeprof.out` задает префикс файлов профиля;
- `prof_final:true` записывает финальный профиль при завершении программы.

После запуска появятся файлы примерно такого вида:

```text
jeprof.out.12345.0.f.heap
```

Это heap profile.

## Анализ в text-формате

```bash
jeprof --text ./app jeprof.out.12345.0.f.heap
```

Пример вывода:

```text
Total: 9.5 MB
     7.8  82.1%  82.1%      7.8  82.1% work()
     1.2  12.6%  94.7%      1.2  12.6% std::string::_M_mutate
```

Упрощенно:

- первая колонка - сколько памяти связано с функцией;
- проценты показывают вклад в общий объем;
- строки выше обычно важнее строк ниже.

## Анализ в графическом виде

SVG:

```bash
jeprof --svg ./app jeprof.out.12345.0.f.heap > heap.svg
```

PDF:

```bash
jeprof --pdf ./app jeprof.out.12345.0.f.heap > heap.pdf
```

В графе узлы - функции.

Ребра - цепочки вызовов.

Большие узлы обычно означают важные места потребления памяти.

## Интерактивный режим

```bash
jeprof ./app jeprof.out.12345.0.f.heap
```

Внутри можно выполнять команды:

```text
top
list work
web
quit
```

Полезные команды:

- `top` показывает самые тяжелые функции;
- `list function_name` показывает строки кода для функции;
- `web` строит граф и открывает его в браузере.

## Сравнение двух профилей

Можно сравнить два heap profile.

Например, было:

```text
before.heap
```

Стало:

```text
after.heap
```

Команда:

```bash
jeprof --text --base=before.heap ./app after.heap
```

Так видно, где память выросла относительно базового профиля.

## Явный dump из программы

Иногда финального профиля мало.

Можно записать профиль в нужной точке программы через `mallctl`.

```cpp
#include <jemalloc/jemalloc.h>

void dump_heap_profile() {
    mallctl("prof.dump", nullptr, nullptr, nullptr, 0);
}
```

Пример:

```cpp
int main() {
    load_config();
    dump_heap_profile();

    run_server();
    dump_heap_profile();
}
```

Так можно получить несколько снимков и сравнить их.

## Если программа не слинкована с jemalloc

Иногда программу нельзя пересобрать.

На Linux можно подменить аллокатор через `LD_PRELOAD`:

```bash
LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libjemalloc.so.2 \
MALLOC_CONF="prof:true,prof_active:true,prof_prefix:jeprof.out,prof_final:true" \
./app
```

На macOS похожая идея - `DYLD_INSERT_LIBRARIES`, но она работает не во всех случаях из-за системных ограничений.

Надежнее явно линковать программу с `jemalloc`.

## Частые проблемы

### Нет файлов профиля

Проверь:

- программа реально использует `jemalloc`;
- в `MALLOC_CONF` есть `prof:true`;
- `jemalloc` собран с поддержкой profiling;
- программа завершилась или был вызван `mallctl("prof.dump", ...)`.

### В профиле нет имен функций

Проверь:

- программа собрана с `-g`;
- бинарник не stripped;
- для оптимизированного кода добавлен `-fno-omit-frame-pointer`.

### Профиль выглядит неполным

`jemalloc` обычно использует sampling.

Это значит: профилируется не каждая аллокация, а выборка.

Меньше `lg_prof_sample` - подробнее профиль, но выше overhead.

## Важно

`jeprof` - не строгий leak checker.

Он показывает, где память выделялась и где она удерживается на момент снимка.

Для поиска ошибок владения полезны и другие инструменты:

- AddressSanitizer;
- LeakSanitizer;
- Valgrind;
- heaptrack.

`jeprof` особенно полезен, когда нужно понять не факт ошибки, а стоимость аллокаций.

## Саммари

- `jemalloc` - аллокатор памяти.
- `jeprof` анализирует heap profile от `jemalloc`.
- Программу лучше собирать с `-g` и `-fno-omit-frame-pointer`.
- Heap profiling включается через `MALLOC_CONF`.
- Основные команды: `jeprof --text`, `jeprof --svg`, `jeprof --pdf`.
- `mallctl("prof.dump", ...)` позволяет сделать снимок вручную.
- `--base` помогает сравнить два профиля.
- `jeprof` показывает потребление памяти, но не заменяет leak checker.
