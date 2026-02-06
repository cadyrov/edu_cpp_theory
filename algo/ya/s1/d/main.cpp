#include <iostream>
#include <cassert>
#include <vector>

int calc(const std::vector<int> &in){
    int res = 0;

    for (int i = 0; i < in.size(); ++i ){
        if (i == 0) {
            if (in[i] > in[i+1]) {
                ++res;
            }

            continue;
        } 

        if (i == in.size()-1) {
            if (in[i] > in[i-1]) {
                ++res;
            }

            continue;
        } 

        
        if (in[i] > in[i-1] && in[i] > in[i+1] ) {
            ++res;
        }

        continue;
    }

    return res;
}

int main() {
    assert(calc({-1,-10,-8,0, 2, 0, 5}) == 3);

    int n;

    std::cin >> n;

    if (n == 1) {
        std::cout << 1;

        return 0;
    }

    std::vector<int> data;
    data.resize(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> data[i];
    }

    std::cout << calc(data);

} 