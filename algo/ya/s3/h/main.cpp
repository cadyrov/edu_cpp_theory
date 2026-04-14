#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int main() {
    int n;
    std::vector<std::string> in{};

    std::cin >> n;
    in.resize(n);

    for (int i = 0; i < n; ++i ) {
        std::cin >> in[i];
    }


    std::sort(in.begin(), in.end(), [](const std::string& a, const std::string& b){ 
        return a[0] > b[0];}
    );



    for (int i = 0; i < n; ++i ) {
        std::cout <<in[i];
    }

    return 0;
}