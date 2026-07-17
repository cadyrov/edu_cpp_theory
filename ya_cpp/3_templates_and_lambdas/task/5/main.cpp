#include <cstdlib>
#include <string>
#include <unordered_map>
#include <iostream>

template<typename Operation> class Cache {
public:
    template<typename T> 
    auto compute(T input) { 
        static std::unordered_map<size_t, decltype(static_cast<Operation *>(this)->Calculate(input))> cache;
        auto key = std::hash<T>{}(input);

        if (cache.find(key) == cache.end()) {
            cache[key] = static_cast<Operation *>(this)->Calculate(input);
        }

        return cache[key];
    }
};

class Fibonacci : public Cache<Fibonacci> {
public:
    size_t Calculate(size_t n) {
        if (n <= 1)
            return n;
        return Calculate(n - 1) + Calculate(n - 2);
    }
};

int main() {

    Fibonacci fib;
    // в первый раз вычисляем
    auto result2 = fib.compute(40);

    std::cout << result2 << "\n";
    // во второй раз достаём значение из кеша
    result2 = fib.compute(40);

    std::cout << result2 << "\n";

    return 0;
}