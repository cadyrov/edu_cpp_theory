#include <print>
#include <string>
#include <vector>
#include <algorithm>

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
    auto first_prime = std::find_if(numbers.begin(), numbers.end(), [](int x) { return is_prime(x); });
    if (first_prime != numbers.end()) {
        std::println("First prime: {}", *first_prime);
    }

    // 2
    bool all_even = std::all_of(numbers.begin(), numbers.end(), [](int x) { return x % 2 == 0; });
    std::println("All even: {}", all_even);

    // 3
    int adjacent_duplicate = -1;
    auto adjacent_duplicate = std::adjacent_find(numbers.begin(), numbers.end());

    // 4
    std::vector<int> other = {4, 6, 4, 4, 6, 8, 10, 13, 14, 14, 15, 15};
    std::pair mismatch_pair = std::mismatch(numbers.begin(), numbers.end(), other.begin());

    // 5
    size_t found_index = std::string::npos;
    auto it = std::search(text.begin(), text.end(), word.begin(), word.end());
    if (it != text.end()) {
        found_index = std::distance(text.begin(), it);
    }
    // Вывод результатов
    if (first_prime != numbers.end()) {
        std::println("First prime: {}", *first_prime);
    }
    std::println("All even: {}", all_even);
    if (adjacent_duplicate != -1) {
        std::println("Adjacent duplicate: {}", adjacent_duplicate);
    }
    if (mismatch_pair.first != numbers.end()) {
        std::println("First mismatch index: {}", mismatch_pair.first - numbers.begin());
    }
    if (found_index != std::string::npos) {
        std::println("Substring found at index: {}", found_index);
    }
} 