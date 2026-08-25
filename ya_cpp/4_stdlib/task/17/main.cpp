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
#include <span>

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
    typename Cont::mapped_type;
};


// Вставка в контейнер
template <typename Cont>
static void BM_AssociativeContLike_Insert(benchmark::State& state) {
    auto data = generateData(state.range(0));

    for (auto _ : state) {
        Cont cont;
        for (int value : data) {
            if constexpr (MapLike<Cont>)
                DoNotOptimize(cont.try_emplace(value, value));
            else
                DoNotOptimize(cont.emplace(value));
        }
    }
}

// Поиск элементов в контейнере
template <typename Cont>
static void BM_AssociativeContLike_Lookup(benchmark::State& state) {
    auto data = generateData(state.range(0));
    Cont cont;

    for (int value : data) {
        if constexpr (MapLike<Cont>)
            cont.try_emplace(value, value);
        else
            cont.emplace(value);
    }

    for (auto _ : state) {
        for (int value : data) {
            DoNotOptimize(cont.find(value));
        }
    }
}

// Итерация по контейнеру
template <typename Cont>
static void BM_AssociativeContLike_Iterate(benchmark::State& state) {
    auto data = generateData(state.range(0));
    Cont cont;

    for (int value : data) {
        if constexpr (MapLike<Cont>)
            cont.try_emplace(value, value);
        else
            cont.emplace(value);
    }

    for (auto _ : state) {
        unsigned int counter = 0;

        for (const auto& element : cont) {
            DoNotOptimize(element);
            ++counter;
        }

        DoNotOptimize(counter);
    }
}

// Регистрируем тесты
#define REGISTER_ASSOCIATIVE_BENCHMARKS(...)                                    \
    BENCHMARK_TEMPLATE(BM_AssociativeContLike_Insert, __VA_ARGS__)              \
        ->Range(10, 100'000)->Iterations(10)->Unit(benchmark::kMicrosecond);    \
    BENCHMARK_TEMPLATE(BM_AssociativeContLike_Lookup, __VA_ARGS__)              \
        ->Range(10, 100'000)->Iterations(10)->Unit(benchmark::kMicrosecond);    \
    BENCHMARK_TEMPLATE(BM_AssociativeContLike_Iterate, __VA_ARGS__)             \
        ->Range(10, 10'000)->Iterations(10)->Unit(benchmark::kMicrosecond)

REGISTER_ASSOCIATIVE_BENCHMARKS(std::map<int, int>);
REGISTER_ASSOCIATIVE_BENCHMARKS(std::unordered_map<int, int>);
REGISTER_ASSOCIATIVE_BENCHMARKS(std::flat_map<int, int>);
REGISTER_ASSOCIATIVE_BENCHMARKS(std::set<int>);
REGISTER_ASSOCIATIVE_BENCHMARKS(std::unordered_set<int>);
REGISTER_ASSOCIATIVE_BENCHMARKS(std::flat_set<int>);

#undef REGISTER_ASSOCIATIVE_BENCHMARKS

// Точка входа для Google Benchmark
BENCHMARK_MAIN();
