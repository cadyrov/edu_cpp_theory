#include <iostream>
#include <string>
#include <vector>

int main() {
    int n;

    std::cin >> n;


    std::vector<int> houses;
    houses.reserve(n);

    int cnt;
    for (int i =0; i < n ;++i) {
        std::cin >> cnt;
        
        houses.push_back(cnt);
    }

    cnt = 0;
    bool first_exists = false;


    for (int i = houses.size() -1;i >=0 ; --i) {
        if (houses[i] == 0) {
            cnt = 0;
            first_exists = true;

            continue;
        }
        ++cnt;

        if (first_exists) {
            houses[i] = cnt;
        }
    }

    cnt = 0;
    first_exists = false;
    
    for (int i = 0;i < houses.size() ; ++i) {
        if (houses[i] == 0) {
            cnt = 0;
            first_exists = true;
            std::cout << houses[i] <<" ";

            continue;
        }

        ++cnt;

        if (first_exists && cnt < houses[i]) {
            houses[i]=cnt;
        }

        std::cout << houses[i] <<" ";
    }


    return 0;
} 