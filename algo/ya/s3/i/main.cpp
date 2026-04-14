#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    int k;
    std::cin >> n;

    struct vus{
        int id = 0;
        int uses = 0;
    };

    std::vector<vus> vuses{};

    vuses.resize(10001);

    int num;
    for (int i = 0; i < n; ++i ) {
        std::cin >> num;
        vuses[num].uses++;
        vuses[num].id = num;
    }

    std::cin >> k;

    std::sort(vuses.begin(), vuses.end(), [](const vus& a, const vus& b) {
        if (a.uses == b.uses) {
            return a.id < b.id;
        }
        return a.uses > b.uses;
    });


    for (int i = 0; i < k ; ++i) {
        if (vuses[i].uses == 0) {
            break;
        }
        std::cout << vuses[i].id << " ";
    }
   

    return 0;
}