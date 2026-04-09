#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> base = {"","", "abc","def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

void process(std::string num,int si, std::string prev) {
   if (si == num.size()) {
        std::cout << prev << " ";

        return;
   }

   for (size_t i = 0; i < base[num[si]-48].size(); ++i) {
        process(num, si+1, prev + base[num[si]-48][i]);
   }
}


int main() {
    std::string n;
    std::cin >> n;

    process(n, 0, "");

    return 0;
}