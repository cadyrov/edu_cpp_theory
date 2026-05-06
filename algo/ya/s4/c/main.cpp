#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

int main() {
    std::string a;
    std::string b;
    std::cin >> a >> b;

    std::unordered_map<char, char> amp;
    std::unordered_map<char, char> bmp;

    if (a.size() != b.size()) {
        std::cout << "NO\n";

        return 0;
    }

    for (int i = 0; i < a.size(); ++i) {
        if (amp.find(a[i]) != amp.end()) {
            if (amp[a[i]] != b[i]) {
                std::cout << "NO\n";
                
                return 0;
            }
        } else {
            amp[a[i]] = b[i];
        }

        if (bmp.find(b[i]) != bmp.end()) {
            if (bmp[b[i]] != a[i]) {
                std::cout << "NO\n";
                
                return 0;
            }
        } else {
            bmp[b[i]] = a[i];
        }
    }

    std::cout << "YES\n";

    return 0;
}