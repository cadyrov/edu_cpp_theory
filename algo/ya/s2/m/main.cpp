#include <iostream>
#include <string>
#include <vector>


int hysto(std::vector<int> &values) {
    std::stack<int> stack;
    std::vector<int> left{};
    left.reserve(values.size());
    std::vector<int> right{};
    right.reserve(values.size());


    for (int i = 0; i < values.size(); ++i) {
        while (!stack.empty() && values[stack.top()] >= values[i]) {
            stack.pop();
        }

        if (stack.empty()) {
            left[i] = -1;
        } else {
            left[i] = stack.top();
        }

        stack.push(i);
    }

    stack = std::stack<int>();

    for (int i = values.size() - 1; i >= 0; --i) {
        while (!stack.empty() && values[stack.top()] >= values[i]) {
            stack.pop();
        }

        if (stack.empty()) {
            right[i] = values.size();
        } else {
            right[i] = stack.top();
        }

        stack.push(i);
    }   

    int max_area = 0;
    for (int i = 0; i < values.size(); ++i) {
        int area = values[i] * (right[i] - left[i] - 1);
        if (area > max_area) {
            max_area = area;
        }
    }

    return max_area;
}

int main() {
    std::vector<int> values{};
    int n;

    std::cin >> n;

    values.reserve(n);
    
    for (int i =0; i < n ;++i) {
        int value;
        std::cin >> value;
        values.push_back(value);
    }

    std::cout << hysto(values) << " ";

    return 0;
}