#include <iostream>
#include <cassert>
#include <string>

bool check(int i) {
    if (i > 47 && i <= 57) {
        return true;
    }

    if (i > 64 && i <= 90) {
        return true;
    }

    if (i > 96 && i <= 122) {
        return true;
    }

    return false;
}

bool equal(int i, int j) {
    if (i==j || (abs(i - j) == 32 &&  i > 64 && j > 64)) {
        return true;
    }

    return false;
}


bool calc(const std::string &in){
    size_t l = 0;
    size_t r = in.size() - 1;

    for (;l < r;) {
        if (!check(in[l])) {
            ++l;

            continue;
        } 

        if (!check(in[r])) {
            --r;
            
            continue;
        } 

        if (!equal(in[l], in[r])) {
            return false;
        }

        --r;
        ++l;
    }

    return true;
}

int main() {
    assert(calc("A man, a plan, a canal: Panama"));

    std::string data;
  
    getline(std::cin, data);
    
    std::cout << (calc(data) ? "True" : "False");

} 