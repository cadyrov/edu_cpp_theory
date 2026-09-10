#include <iostream>

static int current = 0;

class User {

  public:
    User() : id_(current++) {
        std::cout << id_ << " created\n";
    }

    User(const User&) = delete;
    User& operator=(const User&) = delete;

    ~User() {
        std::cout << id_ << " deleted\n";
    }

  private:
    int id_;
};

int main() {
    User x;
    User a;
    User b;

    return 0;
}
