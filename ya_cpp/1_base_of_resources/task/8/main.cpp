// 8. Напишите класс, который логирует конструктор и деструктор, и проверьте вызовы при
// `new/delete`.
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

int main() {
    User* a = new User();
    User* b = new User[5];
    delete a;
    delete[] b;
}

// clang++ --std=c++23 -o main