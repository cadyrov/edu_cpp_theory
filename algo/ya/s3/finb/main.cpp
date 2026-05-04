#include <iostream>
#include <vector>
#include <cassert>
#include <string>

class Candidate {
public:
    std::string name;
    int tasks;
    int fee;

    bool operator<(const Candidate& other) const {
        if (tasks != other.tasks) {
            return other.tasks < tasks;
        }

        if (fee != other.fee) {
            return other.fee > fee;
        }

        return name < other.name;
    }
};




void sort(std::vector<Candidate>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    Candidate pivot = arr[left + (right - left)/2];
    int l = left;
    int r = right;

    while (l <= r) {
        while (arr[l] < pivot) {
            ++l;
        }
        while (pivot < arr[r]) {
            --r;
        }
        if (l <= r) {
            std::swap(arr[l], arr[r]);
            ++l;
            --r;
        }
    }

    sort(arr, left, r);
    sort(arr, l, right);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Candidate> arr(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i].name;
        std::cin >> arr[i].tasks;
        std::cin >> arr[i].fee;
    }

    sort(arr, 0, arr.size() - 1);

    for (Candidate c :arr) {
        std::cout << c.name << '\n';
    }

    return 0;
}