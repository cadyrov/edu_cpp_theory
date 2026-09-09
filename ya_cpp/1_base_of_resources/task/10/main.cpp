// 8.  Напишите функцию, где при раннем `return` легко забыть `delete`..
#include <iostream>

class User {
  public:
    User() {
        std::cout << "created" << "\n";
    }

    ~User() {
        std::cout << "deleted" << "\n";
    }
};

bool make(bool ret = false) {
    User* s = new User();
    delete s;

    return true;
};

int main() {
    std::cout << make(false) << "\n";
}

// clang++ --std=c++23 -o main