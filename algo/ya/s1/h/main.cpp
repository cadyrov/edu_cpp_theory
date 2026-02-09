#include <iostream>
#include <cassert>
#include <string>
#include <vector>


std::vector<char> calc(const std::string &first, const std::string &second) {
    std::vector<char> dst;
    dst.reserve(std::max(first.size(), second.size()) + 1);
    
    int add = 0;
    int i  = first.size() - 1;
    int j  = second.size() - 1;

    for (; i >= 0 && j >= 0; --i, --j) {
        int sum = (first[i] - '0') + (second[j] - '0') + add;
        
        dst.push_back((sum % 2) + '0');
        
        add = sum / 2;
    }
    
    for (; i >= 0; --i) {
        int sum = (first[i] - '0') + add;
        dst.push_back((sum % 2) + '0');
        add = sum / 2;
    }

    for (; j >= 0; --j) {
        int sum = (second[j] - '0') + add;
        dst.push_back((sum % 2) + '0');
        add = sum / 2;
    }

    if (add) {
        dst.push_back(add + '0');
    }

    return dst;
}

int main() {


    std::string first, second;

    getline(std::cin, first);
    getline(std::cin, second);

    std::vector<char> dst = calc(first, second);

    for (auto it = dst.rbegin(); it != dst.rend(); ++it) {
        std::cout << *it;
    }
} 