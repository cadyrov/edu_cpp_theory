#include <iostream>
#include <cassert>
#include <vector>

void calc(const std::vector<std::vector<int>> &in, int x, int y, std::vector<int> &out){
    if (x < in.size()-1) {
        out.emplace_back(in[x+1][y]);
    }

    if (y < in[x].size()-1) {
        out.emplace_back(in[x][y+1]);
    }

    if (x > 0) {
        out.emplace_back(in[x-1][y]);
    }
    
    if (y > 0) {
        out.emplace_back(in[x][y-1]);
    }
    
}

int main() {
    int a;
    int b; 
    int x;
    int y; 

    std::cin >> a >> b;

    std::vector<std::vector<int>> data;
    data.reserve(a);

    for (int i = 0; i < a; ++i) {
        std::vector<int> datax;
        datax.resize(b);

        for (int j = 0; j < b; ++j) {
            std::cin >> datax[j];
        }

        data.emplace_back(datax);
    }

    std::cin >> x >> y;

    std::vector<int> dst;
    dst.reserve(4);

    calc(data, x, y, dst);

    for (int i = 0; i < dst.size(); ++i) {
        std::cout << dst[i] << " ";
    }
} 