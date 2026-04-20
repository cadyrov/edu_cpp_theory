#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main() {
    int n;
    int k;
    std::cin >> n;

    std::vector<int> plates{};

    plates.resize(n);

    for (int i = 0; i < n; ++i ) {
        std::cin >> plates[i];
    }

    std::cin >> k;

    std::sort(plates.begin(), plates.end());

    // в отсортированном массиве минимальная разница будет у соседних первых элементов
    // масимвальная у первого и последнего

    // для каждого целого числа между ними мы по массиву ищем количеству разниц бинарным поиском
    // это условно квадратичный алгоритм но ограничение в остортированом массиве будет дистанция

    // опредлим функцию нахождения количества чисел меньше или равной разнице для числа n

    auto diff = [](const std::vector<int>& in, int df ){
        int result = 0;
        for (int i = 0; i < in.size() - 1; ++i) {
            for (int j = i + 1; j < in.size(); ++j) {
                if (in[j] - in[i] <= df) {
                    ++result;
                }
            }
        }
        return result;
    };

    assert(diff(std::vector<int>{1,2,3,4}, 2) == 5);
    assert(diff(std::vector<int>{1,1,3,4}, 1) == 2);


    int min_diff = 0;
    int max_diff = plates[plates.size() - 1] - plates[0];

    while (min_diff < max_diff) {
        int mid_diff = min_diff + (max_diff - min_diff) / 2;
        int count = diff(plates, mid_diff);

        if (count >= k) {
            max_diff = mid_diff;
        } else {
            min_diff = mid_diff + 1;
        }
    }

    std::cout << min_diff << std::endl;
    

    return 0;
}