#include <chrono>
#include <map>
#include <random>
#include <set>
#include <vector>
#include <print>

#include <flat_map>
#include <flat_set>

template <class Tp>
inline __attribute__((always_inline)) void DoNotOptimize(Tp &&value) {
#if defined(__clang__)
    asm volatile("" : "+r,m"(value) : : "memory");
#else
    asm volatile("" : "+m,r"(value) : : "memory");
#endif
}

constexpr const size_t N = 100'000;
constexpr const size_t ITERATIONS = 30;

std::vector<int> generateData(size_t count) {
    std::vector<int> data(count);

    std::mt19937 gen{42};
    std::uniform_int_distribution<int> dist(1, N);
    for (auto it = data.begin(); it != data.end(); ++it) {
        *it = dist(gen);
    }

    return data;
}

const auto data = generateData(N);

auto measureExec(auto f) {
    long long total = 0;

    for (size_t i = 0; i < ITERATIONS; ++i) {
        auto start = std::chrono::steady_clock::now();
        f();
        auto end = std::chrono::steady_clock::now();

        total += std::chrono::duration_cast<std::chrono::milliseconds>(
            end - start
        ).count();
    }

    return total / ITERATIONS;
};

template <typename Cont>
auto measureInsertion() {
    return measureExec([] {
        Cont cont;

        for (int v : data) {
            if constexpr (requires { cont.try_emplace(v, v); })
                DoNotOptimize(cont.try_emplace(v, v)); 
            else
                DoNotOptimize(cont.emplace(v));     
        }
    });
};

template <typename Cont>
auto measureContains() {
    Cont cont;

    for (int v : data) {
        if constexpr (requires { cont.try_emplace(v, v); })
            cont.try_emplace(v, v); 
        else
            cont.emplace(v);       
    }

    return measureExec([&cont] {
        for (int i = 0; i < 10; ++i)
            for (int v : data)
                DoNotOptimize(cont.contains(v));
    });
};

void benchmarkSetVsFlatSet() {
    std::print("std::set::emplace time:  {:>5}ms, Number of iterations: {:>5}\n", measureInsertion<std::set<int>>(),
               ITERATIONS);
    std::print("std::set::contains time: {:>5}ms, Number of iterations: {:>5}\n", measureContains<std::set<int>>(),
               ITERATIONS);
    std::println();

    std::print("std::flat_set::emplace time: {:>5}ms, Number of iterations: {:>5}\n",
               measureInsertion<std::flat_set<int>>(), ITERATIONS);
    std::print("std::set::contains time:     {:>5}ms, Number of iterations: {:>5}\n",
               measureContains<std::flat_set<int>>(), ITERATIONS);
    std::println();
}

void benchmarkMapVsFlatMap() {
    std::print("std::map::emplace time:  {:>5}ms, Number of iterations: {:>5}\n",
               measureInsertion<std::map<int, int>>(), ITERATIONS);
    std::print("std::map::contains time: {:>5}ms, Number of iterations: {:>5}\n", measureContains<std::map<int, int>>(),
               ITERATIONS);
    std::println();

    std::print("std::flat_map::emplace time:  {:>5}ms, Number of iterations: {:>5}\n",
               measureInsertion<std::flat_map<int, int>>(), ITERATIONS);
    std::print("std::flat_map::contains time: {:>5}ms, Number of iterations: {:>5}\n",
               measureContains<std::flat_map<int, int>>(), ITERATIONS);
    std::println();
}

int main() {
    std::print("=== std::set vs flat_set ===\n");
    benchmarkSetVsFlatSet();

    std::print("\n\n=== std::map vs flat_map ===\n");
    benchmarkMapVsFlatMap();

    return 0;
} 