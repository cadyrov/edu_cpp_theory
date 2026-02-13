#include <iostream>
#include <string>

int main() {
    std::string first;
    std::string second;

    getline(std::cin, first);
    getline(std::cin, second);

    int diff=0;

    for (int i = 0;i < first.size() ; ++i) {
        diff += first[i];
    }

    for (int i = 0;i < second.size() ; ++i) {
        diff -= second[i];
    }

    std::cout << char(abs(diff));
} 