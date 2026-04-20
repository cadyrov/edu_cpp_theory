#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

long long binDiff(const std::vector<long long>& in, int k) {
    auto diff = [](const std::vector<long long>& in, long long df ){
        long long result = 0;
        for (int i = 0; i < in.size() - 1; ++i) {
            // Проверяем переполнение перед сложением
            long long target = in[i] + df;
            auto it = std::upper_bound(in.begin() + i + 1, in.end(), target);
            result += std::distance(in.begin() + i + 1, it);
        }
        return result;
    };

    long long min_diff = 0;
    long long max_diff = in[in.size() - 1] - in[0];

    while (min_diff < max_diff) {
        long long mid_diff = min_diff + (max_diff - min_diff) / 2;
        long long count = diff(in, mid_diff);

        if (count >= k) {
            max_diff = mid_diff;
        } else {
            min_diff = mid_diff + 1;
        }
    }

    return min_diff;
}


int main() {
    int n;
    int k;
    std::cin >> n;

    std::vector<long long> plates{};

    plates.resize(n);

    for (int i = 0; i < n; ++i ) {
        std::cin >> plates[i];
    }

    std::cin >> k;

    std::sort(plates.begin(), plates.end());

    std::cout << binDiff(plates, k) << std::endl;
    

    return 0;
}

