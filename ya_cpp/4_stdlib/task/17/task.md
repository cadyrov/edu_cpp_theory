Представьте, что вы работаете в отделе оптимизации и профилирования кода и консультируете команды по вопросам выбора оптимальных контейнеров. Чтобы упростить процесс принятия решения, вы решили воспользоваться Google benchmark и создать универсальную систему тестирования для сравнения производительности ассоциативных контейнеров.

Скопируйте код ниже к себе и выполните задания:
- Разработайте концепт MapLike, который может работать с ассоциативными контейнерами хранящими не только значение, но и ключ.
- Разработайте функцию BM_AssociativeContLike_Insert, которая:
- Использует шаблонный параметр для определения типа контейнера.
- Принимает в качестве единственного аргумента benchmark::State& state.
- Получает из state один аргумент - количество элементов.
- Вызывает generateData с заданным параметром.
- Тестирует операцию вставки в контейнер с использованием benchmark::DoNotOptimize().

По аналогичному шаблону разработайте функции BM_AssociativeContLike_Lookup и BM_AssociativeContLike_Iterate.
- Зарегистрируйте по три теста для каждого из следующих контейнеров: std::map, std::unordered_map, std::flat_map.
- Зарегистрируйте по три теста для каждого из следующих контейнеров: std::set, std::unordered_set, std::flat_set.
- Настройте запуск тестов Lookup и Insertion с количеством элементов в диапазоне от 10 до 100'000.
- Настройте запуск тестов Iterate с количеством элементов в диапазоне от 10 до 10'000.
- Настройте вывод результатов в микросекундах, а количество итераций равным 10.

```cpp
#include <benchmark/benchmark.h>
#include <vector>
#include <map>
#include <flat_map>
#include <unordered_map>
#include <set>
#include <flat_set>
#include <unordered_set>
#include <random>
#include <algorithm>

using benchmark::DoNotOptimize;

std::unordered_map<size_t, std::vector<int>> cachedData;

const std::span<int> generateData(size_t N) {

    auto it = cachedData.find(N);
    if (it != cachedData.end()) {
        return it->second;
    }

    std::vector<int> data;
    data.reserve(N);

    for (int i = 0; i < N; ++i) {
        data.emplace_back(i);
    }

    // Перемешиваем вектор, чтобы порядок вставок был случайным
    std::shuffle(data.begin(), data.end(), std::mt19937{42});

    auto newIt = cachedData.try_emplace(it, N, std::move(data));
    return newIt->second;
}

template <typename Cont>
concept MapLike = requires(Cont cont) {
    // Ваш код здесь
};


// Вставка в контейнер
template <typename Cont>
static void BM_AssociativeContLike_Insert(benchmark::State& state) {
}

// Поиск элементов в контейнере
template <typename Cont>
static void BM_AssociativeContLike_Lookup(benchmark::State& state) {
}

// Итерация по контейнеру
template <typename Cont>
static void BM_AssociativeContLike_Iterate(benchmark::State& state) {
}

// Регистрируем тесты

// Точка входа для Google Benchmark
BENCHMARK_MAIN(); 
```

- Используйте state.range(0) чтобы получить первый аргумент из переменной state бенчмарка.
- Примените if constexpr (MapLike<Cont>), чтобы избежать дублирования кода для контейнеров SetLike и MapLike.
- Для оценки скорости итерации по контейнеру вы можете создать unsigned int counter; и увеличивать его для каждого элемента.
- Примените ->Range(start, end), чтобы задать диапазон тестируемых значений для первого аргумента.
- Примените ->Iterations(10) чтобы указать, сколько раз надо запускать тест для каждого аргумента.