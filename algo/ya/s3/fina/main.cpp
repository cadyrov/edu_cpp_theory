#include <iostream>
#include <vector>
#include <cassert>

int broken_search(const std::vector<int>& vec, int k) {
    int l = 0;
    int r = vec.size() -1;
    int m = 0;

    for (;l <= r;) {
        m = l + (r -l)/2;

        //std::cout << l << " " << r << " " << m <<
        //" l:" << vec[l] << " m:" << vec[m] << " r:" << vec[r]  << std::endl;

        if (vec[l] == k) {
            return l;
        }

        if (vec[r] == k) {
            return r;
        }

        if (vec[m] == k) {
            return m;
        }


        if (vec[l] < vec[r]) {
            if (vec[m] > k) {
                r = m-1;
            } else {
                l = m+1;
            }
        } else {
            if (vec[m] > k && vec[l] < k && vec[r] < k) {
                r = m-1;
            }else if (vec[m] > k  && vec[l] >k && vec[l] > vec[m]) {
                r = m-1;
            }else if (vec[m] < k  && vec[l] <k && vec[r] > k) {
                r = m-1;
            }else if (vec[m] < k  && vec[l] < k && vec[l] > vec[m]) {
                r = m-1;
            }else {
                l = m+1;
            }
        }
    }

    return -1;
}

void test() {
    std::vector<int> arr = {19, 21, 100, 101, 1, 4, 5, 7, 12};
    assert(6 == broken_search(arr, 5));
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> arr(n);

    test();

    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    std::cout << broken_search(arr, k) << std::endl;

    return 0;
}