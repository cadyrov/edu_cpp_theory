#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


int process(std::vector<int> childs, std::vector<int> cookies) {
     std::sort(childs.begin(), childs.end());
     std::sort(cookies.begin(), cookies.end());

     size_t ch_i = 0;
     size_t co_i = 0;
     int result = 0;

     for (;ch_i < childs.size() && co_i < cookies.size();) {
          if (childs[ch_i] <= cookies[co_i]) {
               ++ch_i;
               ++result;
          }

          ++co_i;
     }

     return result;
}


int main() {
     int child_n;
     std::vector<int> childs;
     int cookies_n;
     std::vector<int> cookies;

     std::cin >> child_n;
     childs.resize(child_n);

     for (int i = 0; i < child_n; ++i) {
          std::cin >> childs[i];
     }

     std::cin >> cookies_n;
     cookies.resize(cookies_n);

     for (int i = 0; i < cookies_n; ++i) {
          std::cin >> cookies[i];
     }

     std::cout  << process(childs, cookies);

     return 0;
}