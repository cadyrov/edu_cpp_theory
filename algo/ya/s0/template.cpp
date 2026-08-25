#include <iostream>

using namespace std;

int main() {
    int num_lines;
    cin >> num_lines;
    for (int i = 0; i < num_lines; ++i) {
        int value_1, value_2;
        cin >> value_1 >> value_2;
        int result = value_1 + value_2;
        cout << result << '\n';
    }
    return 0;
}