#include <iostream>
#include <string>
#include <vector>

int main() {
    int k;
    std::string vv;

    getline(std::cin, vv);
    k = std::stoi(vv);


    int digits[10] = {0,0,0,0,0,0,0,0,0,0};
    
    
    for (int i =0; i < 4 ;++i) {
        getline(std::cin, vv);
        
        for (int j = 0; j < vv.size(); j++) {
            if (vv[j] != '.') {
                ++digits[int(vv[j] - '0')];
            }
        }
    }

    int cnt = 0;

    for (int i = 1; i <10; ++i) {
        if (digits[i] <= k*2 && digits[i] != 0) {
            ++cnt;
        }
    }


    std::cout << cnt;

    return 0;
} 