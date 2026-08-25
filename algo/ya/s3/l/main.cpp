#include<iostream>
#include<vector>


int binary(const std::vector<int>& data, int aim, int left) {
    int right = data.size() -1;
    if (left < 0) {
        left = 0;
    }
    int mid;

    if (data[right] < aim) {
        return -1;
    }

    for (;right > left;) {
        if (data[left] >= aim) {
            return left;
        }

        mid = (right - left)/2 + left;

        if (data[mid] >= aim) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

int main() {
    int days;
    std::vector<int> data;
    int cost;

    std::cin >> days;
    data.resize(days);

    for (int i = 0; i < days; ++i) {
       std::cin >> data[i];
    }

    std::cin >> cost;


    int first = binary(data, cost, 0);
    int second = binary(data, cost*2, first);

    std::cout << (first == -1 ? first : first+1) << " ";

    std::cout << (second == -1 ? second : second+1);
    return 0;
}