#include <iostream>
#include <string>




void brac(int open, int close, int n, std::string in) {
    if (open == n && close == n) {
        std::cout << in << std::endl;
    }

    if (open < n) {
        in.push_back('(');
        brac(open+1, close, n, in);
        in.pop_back();
    }

     if (close < open) {
        in.push_back(')');
        brac(open, close+1, n, in);
        in.pop_back();
    }
  
}


int main() {
    int n;
    std::cin >> n;

    brac(0, 0, n, "");

    return 0;
}