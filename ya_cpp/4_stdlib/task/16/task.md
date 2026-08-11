Ваша компания разрабатывает высоконагруженные сервисы. С выходом C++23 руководитель попросил вас присмотреться к новым плоским контейнерам. Ваша задача - замерить производительность самых популярных сценариев, в которых используется std::set и std::map, и спрогнозировать, станет ли программа быстрее при замене этих контейнеров на новые плоские аналоги.

Скопируйте код ниже к себе и выполните задания:

Реализуйте функцию measureExec, которая:
- Принимает на вход лямбда-функцию для запуска.
- Запускает функцию ITERATIONS раз, каждый раз замеряя время выполнения.
- В качестве результата выводит среднее время в мс.

Измерить время выполнения функции поможет конструкция:

- std::chrono::steady_clock::now();
- std::chrono::duration_cast<chrono::milliseconds>(end - start).count(); 

Реализуйте функцию measureInsertion, которая:
- В качестве шаблонного параметра принимает на вход тип контейнера.
- Измеряет скорость вставки с помощью measureExec методом emplace для *set и try_emplace для *map.
- Одна итерация теста вставки элементов подразумевает вставку всех элементов из data.

Реализуйте функцию measureContains, которая:
- Принимает на вход в качестве шаблонного параметра тип контейнера
- Измеряет скорость поиска элементов с помощью measureExec методом contains.
- Одна итерация теста поиска элементов подразумевает поиск всех элементов из data 10 раз подряд.
Ко всем операциям, время которых вы хотите измерить, примените специальную функцию DoNotOptimize, например: DoNotOptimize(cont.emplace(v));

```cpp
#include <chrono>
#include <map>
#include <random>
#include <set>
#include <vector>

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
    std::vector<int> results;

    // Ваш код здесь

    return res / results.size();
};

template <typename Cont>
auto measureInsertion() {

};

template <typename Cont>
auto measureContains() {

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
```

- Функцию measureExec сделайте шаблонной, но вместо template можно использовать auto: auto measureExec(auto f).
- Для измерения времени в функции measureExec запускайте переданную лямбду строго между *::now();.
- Чтобы применить разные методы для контейнеров SetLike и MapLike, используйте if constexpr requires в measureInsertion и measureContains.