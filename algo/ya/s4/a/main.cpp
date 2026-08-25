#include <iostream>
#include <set>
#include <string>
#include <cstdlib>

int main() {
    std::string current;

    std::getline(std::cin, current);

    int n = std::atoi(current.c_str());

    std::set<std::string> st;
    

    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, current);

        if (st.find(current) == st.end()) {
            std::cout << current << '\n';

            st.emplace(current);
        }
    }


    return 0;
}