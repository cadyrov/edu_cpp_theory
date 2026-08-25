#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

long long binDiff(const std::vector<long long>& in, long long k) {
    auto diff = [](const std::vector<long long>& in, long long df ){
        long long result = 0;
        for (int i = 0; i < in.size() - 1; ++i) {
            auto it = std::upper_bound(in.begin() + i + 1, in.end(), in[i] + df);
            result += (it - (in.begin() + i + 1));
        }
        return result;
    };

    long long min_diff = 0; 
    long long max_diff = in[in.size() - 1] - in[0];

    while (min_diff < max_diff) {
        long long mid_diff = min_diff + ((max_diff - min_diff) >> 1);
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
    long long k;
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

