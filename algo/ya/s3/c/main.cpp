#include <iostream>
#include <string>
#include <vector>


bool process(const std::string& a,const std::string& b) {
     int ai = 0;
     int bi = 0;

     for (;ai < a.size() && bi < b.size();) {
          if (a[ai] == b[bi]) {
               ai++;
               bi++;

               if (ai == a.size()) {
                    return true;
               }

               continue;
          }

          bi++;
     }

     return false;
}


int main() {
     std::string a;
     std::string b;
   
     getline(std::cin, a);
     getline(std::cin, b);

     process(a, b)? std::cout << "True" : std::cout << "False";

     return 0;
}