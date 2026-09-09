// 5. Выделите память через `malloc` и освободите через `free`.
#include <iostream>
#include <stdexcept>

class User {
  public:
    int id;

    friend std::ostream& operator<<(std::ostream& os, const User& us) {
        os << "user: " << us.id;

        return os;
    }
};

int main() {
    void* mem = malloc(sizeof(User));
    if (mem == nullptr) {
        throw std::bad_alloc();
    }

    User* p = new (mem) User(33);

    std::cout << *p << "\n";

    p->~User();

    free(mem);

    return 0;
}

// clang++ --std=c++23 -o main