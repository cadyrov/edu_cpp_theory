#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>



int hash(std::string& s) {
    std::sort(s.begin(), s.end());
    
    int h = 0;

    int base = 41;
    int mod = (1 << 30) - 1;

    long long current_base = 1;

    for (char c : s) {
        h = (h * current_base + c) % mod;
        current_base = (current_base * base) % mod;
    }

    return h;
}

int main() {
    int n;
    std::string in;

    std::map<int, std::vector<int>> word_count;

    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> in;
        
        word_count[hash(in)].push_back(i);
    }


    std::vector<std::vector<int>> groups;
    groups.reserve(word_count.size());
    
    for (const auto& p : word_count) {
        groups.emplace_back(std::move(p.second));
    }

    std::sort(groups.begin(), groups.end());

    
    for (const auto& group : groups) {
        for (int i : group) {
            std::cout << i << " ";
        }

        std::cout << std::endl;
    }
}