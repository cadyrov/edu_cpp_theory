Разработчикам часто приходится анализировать уже существующий код, искать в нём паттерны и закономерности и применять функции из стандартной библиотеки алгоритмов для улучшения кода. Попрактикуйтесь в этом деле. 

Скопируйтк код ниже к себе, проанализируйте его и перепишите с помощью алгоритмов из стандартной библиотеки. Результат работы кода не должен измениться.
```cpp
#include <print>
#include <string>
#include <vector>

bool is_prime(int n) {
    if (n < 2)
        return false;
    for (int d = 2; d * d <= n; ++d)
        if (n % d == 0)
            return false;
    return true;
}

int main() {
    std::vector numbers = {4, 6, 4, 4, 6, 8, 10, 13, 14, 14, 14, 15};
    std::string text = "This is a very long text and I want to use the most efficient algoritm here";
    std::string word = "algoritm";

    // 1
    int first_prime = -1;
    for (int x : numbers) {
        if (is_prime(x)) {
            first_prime = x;
            break;
        }
    }

    // 2
    bool all_even = true;
    for (int x : numbers) {
        if (x % 2 != 0) {
            all_even = false;
            break;
        }
    }

    // 3
    int adjacent_duplicate = -1;
    for (size_t i = 0; i + 1 < numbers.size(); ++i) {
        if (numbers[i] == numbers[i + 1]) {
            adjacent_duplicate = numbers[i];
            break;
        }
    }

    // 4
    std::vector<int> other = {4, 6, 4, 4, 6, 8, 10, 13, 14, 14, 15, 15};
    size_t mismatch_index = -1;
    for (size_t i = 0; i < std::min(numbers.size(), other.size()); ++i) {
        if (numbers[i] != other[i]) {
            mismatch_index = i;
            break;
        }
    }

    // 5
    size_t found_index = std::string::npos;
    for (size_t i = 0; i + word.size() <= text.size(); ++i) {
        if (text.substr(i, word.size()) == word) {
            found_index = i;
            break;
        }
    }

    // Вывод результатов
    std::println("First prime: {}", first_prime);
    std::println("All even: {}", all_even);
    std::println("Adjacent duplicate: {}", adjacent_duplicate);
    std::println("First mismatch index: {}", mismatch_index);
    std::println("Substring found at index: {}", found_index);
} 
```

- В каждой части кода примените один из алгоритмов: std::adjacent_find, std::all_of, std::find_if, std::boyer_moore_searcher или std::mismatch.
- Если результат работы алгоритма ― итератор, сравните его с container.end() и в итоговую переменную (например, mismatch_index) выведите - -1 или искомое значение.
- Не меняйте код вывода результатов.
- Ваш код не должен содержать циклы for.