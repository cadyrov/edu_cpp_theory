#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;

    struct clumb{
        int start = 0;
        int end = 0;
    };

    std::vector<clumb> clumbs{};

    clumbs.resize(n);

    clumb cl{};
    for (int i = 0; i < n; ++i ) {
        std::cin >> clumbs[i].start;
        std::cin >> clumbs[i].end;
    }


    std::sort(clumbs.begin(), clumbs.end(), [](const clumb& a, const clumb& b) {
       return a.start < b.start;
    });

    int l = 0;
    int r = 1;

    for (; r < n;) {
        if (clumbs[l].end < clumbs[r].start) {
            ++l;
            clumbs[l] = clumbs[r];
            ++r;

            continue;
        }

        if (clumbs[l].end < clumbs[r].end) {
            clumbs[l].end = clumbs[r].end;
        }

        ++r;
    }



    for (int i = 0; i <= l ; ++i) {
        std::cout << clumbs[i].start << " " << clumbs[i].end << "\n";
    }
   

    return 0;
}