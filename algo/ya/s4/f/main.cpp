#include <iostream>
#include <string>
#include <vector>

int main() {
    long long base;
    long long mod;
    std::string str;
    int queries;
    std::cin >> base >> mod >> str >> queries;

    std::vector<long long> hash(str.size() + 1, 0);
    std::vector<long long> pow(str.size() + 1, 1);


    long long current_base = 1;

    for (int i = 0; i < str.size(); ++i) {
        hash[i+1] = (hash[i] * base + str[i]) % mod;
        pow[i+1] = (pow[i] * base) % mod;
    }


    for (int i = 0; i < queries; ++i) {
        int l, r;
        std::cin >> l   >> r;

        std::cout << (hash[r] - hash[l-1] * pow[r-l+1] % mod + mod) % mod << std::endl;
    }
}