#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>


int sequence_count(const std::vector<int> &first, const std::vector<int> &second) {
    int count = 0;
    int left_idx;
    int current_cnt = 0;

    for (int i =0; i < first.size(); ++i) {
        left_idx = i;
        for (int j =0; j < second.size(); ++j) {
            if (first[left_idx] == second[j] && left_idx < first.size()) {
                ++current_cnt;
                ++left_idx;
            } else {
                left_idx = i;
                if (current_cnt > count) {
                    count = current_cnt;
                }
                current_cnt = 0;
            }
        }
        if (current_cnt > count) {
            count = current_cnt;
        }
        current_cnt = 0;
    }

    return count;
}

int main() {
    assert(sequence_count({1,2,3,2,1}, {3,2,1,5,6}) == 3);
    assert(sequence_count({1,2,3,4,5}, {4,5,9}) == 2);

    int f_count;
    int s_count;

    std::cin >> f_count;
    std::vector<int> first(f_count);

    for (int i =0; i < f_count; ++i) {
        std::cin >> first[i];
    }

    std::cin >> s_count;
    std::vector<int> second(s_count);

    for (int i =0; i < s_count; ++i) {
        std::cin >> second[i];
    }
    
    std::cout << sequence_count(first, second);

    return 0;
}