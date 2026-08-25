#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    std::string in;

    std::cin >> in;

    int l = 0; 
    int r = 0;

    int max = 1;

    std::map<char, int> chars;

    while (r < in.size()) {
    if (chars[in[r]] > 0) {
        --chars[in[l]];
        ++l;
    } else {
        ++chars[in[r]];
        max = std::max(max, r - l + 1);
        ++r;
    }
}
    std::cout << max << std::endl;

    return 0;
}