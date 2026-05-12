#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

int main() {
    int n;
    long long sum;

    std::cin >> n >> sum;

    std::vector<long long> numbers(n);

    if (n ==0) {
        std::cout << 0 << '\n';
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    std::unordered_map<long long, std::vector<std::vector<int>>> numbers_map;

    for (int i = 0; i < numbers.size()-1; ++i) {
        for (int j = i+1; j < numbers.size(); ++j) {
            numbers_map[numbers[i] + numbers[j]].push_back(std::vector<int>{i, j});
        }
    }

    std::set<std::vector<long long>> result; 


    for (int i = 0; i < numbers.size()-1; ++i) {
        for (int j = i+1; j < numbers.size(); ++j) {
            auto vc = numbers_map.find(sum - numbers[i] - numbers[j]);
            if (vc != numbers_map.end()) {
                for (int p =0; p < (*vc).second.size(); ++p) {
                    int idx1 = (*vc).second[p][0];
                    int idx2 = (*vc).second[p][1];
                    if (idx1 != i && idx1 != j && idx2 != i && idx2 != j) {
                        std::vector<long long> quad = {numbers[idx1], numbers[idx2], numbers[i], numbers[j]};
                        std::sort(quad.begin(), quad.end());
                        result.insert(quad);
                    }
                }
            }
        }
    }

    std::cout << result.size() << '\n';
    for (auto quad :result) {
        std::cout << quad[0] << " " << quad[1] << " " 
            << quad[2] << " " << quad[3] << '\n';
    }

}