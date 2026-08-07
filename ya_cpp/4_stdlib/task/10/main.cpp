#include<vector>
#include<span>
#include<algorithm>
#include<cassert>
#include<mdspan>
#include<iostream>


void process(std::span<int> s) {
    std::for_each(s.begin(), s.end(),
        [](auto& x) {
        x *= x;
    });
};

void print(std::mdspan<int, std::extents<size_t, 3, 3>> in) {
    for (size_t i = 0; i < in.extent(0);++i) {
        for (size_t j = 0; j < in.extent(1);++j) {
            std::cout << in[i, j] << " ";
        }
        std::cout << "\n";
    }
};

void main() {
  std::vector v = {1, 2, 3};
  process(v);
  assert((v == std::vector{1, 4, 9}));

  std::vector x = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::mdspan<int, std::extents<size_t, 3, 3>> matrix(x.data());
  print(matrix);
} 



