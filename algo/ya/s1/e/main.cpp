#include <iostream>
#include <cassert>
#include <string>

std::string calc(const std::string &in){
    std::string res = "";
    size_t pos = 0;

    for (size_t i = 0; i < in.size(); ++i) {
        if (in[i] == ' ') {
            if (i - pos > res.size()) {
                res = in.substr(pos, i - pos);
            }

            pos = i + 1;
        }
    }

    if (in.size() - pos > res.size()) {
        res = in.substr(pos, in.size() - pos);
    }

    return res;
}

int main() {
    assert(calc("i love segment tree") == "segment");
    //assert(calc("ligf kaakm") == "kaakm");

    std::string data;
  
    getline(std::cin, data);
    getline(std::cin, data);

    data = calc(data);
    
    std::cout << data << "\n" << data.size();

} 