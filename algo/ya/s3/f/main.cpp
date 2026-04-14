#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int main() {
    int n;
    std::vector<int> in{};

    std::cin >> n;
    in.resize(n);

    for (int i = 0; i < n; ++i ) {
        std::cin >> in[i];
    }

    std::sort(in.begin(), in.end(), [](int a, int b){
        return a > b;
    });

    for (int i = 0; i < in.size()-2; ++i ) {
        if (in[i] < in[i+1] + in[i+2]) {
            std::cout << in[i] + in[i+1] + in[i+2];

            return 0;
        }
    }

    return 0;
}