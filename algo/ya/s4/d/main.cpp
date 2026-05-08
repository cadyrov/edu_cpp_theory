#include <iostream>
#include <string>

int main() {
    long long base;
    long long mod;
    std::string str;
    long long result = 0;

    std::cin >> base >> mod >> str;
    
    long long current_base = 1;
    for (long long i = str.size()-1; i >=0; --i) {
        
       result += ((str[i])*current_base)%mod;
       result %= mod;

       current_base = (current_base * base) % mod;
    }

    std::cout << result << "\n";

    return 0;
}