#include <iostream>
#include <vector>
#include <unordered_map>


int calculate(const std::vector<int>& arr) {
    std::unordered_map<int,int> mp;
    mp.insert({0, -1});

    int result = 0;
    int sum = 0;

    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == 0) {
            --sum;
        } else {
            ++sum;
        }

        auto it = mp.find(sum);
        if (it != mp.end()) {
            if (i - it->second >  result) {
                result = (i - it->second);
            }
        } else {
            mp.insert({sum, i});
        }
    }

    return result;
}   

int main() {
    int n;
    std::cin >> n;

    std::vector<int> st(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> st[i];
    }


    std::cout << calculate(st) << '\n';


    return 0;
}