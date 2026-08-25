#include <iostream>
#include <cassert>
#include <string>
#include <vector>

int main() {
    int n;
    int k;
    std::vector<int> x;

    std::cin >> n;
    x.reserve(n);

    for (int i = 0;i < n ; ++i) {
        int y;
        std::cin >> y;

        x.push_back(y);
    }

    std::cin >> k;

    for(size_t i = 0, j = x.size() - 1; i < j; i++, j--){
        std::swap(x[i], x[j]);
    }

    int i = 0;
    int add = 0;

    for(;k > 0;){
       int m = k%10 + add;
       
       if (i >= x.size()) {
          x.push_back(m%10);
       } else {
          m += x[i];
          x[i] = m%10;
       }

       add = m/10;
       k /= 10;
       ++i;
    }

    if (add > 0) {
        x.push_back(add);
    }

    for (auto it = x.rbegin(); it != x.rend(); ++it) {
        std::cout << *it << " ";
    }   
} 