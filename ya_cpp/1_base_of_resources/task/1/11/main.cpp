// Создайте объект User в alignas(User) std::byte buffer[sizeof(User)] через placement new, затем
// разрушьте вручную
#include <cstddef>
#include <iostream>
#include <new>

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
    alignas(User) std::byte buffer[sizeof(User)];
    User* u = new (buffer) User();
    u->~User();
}

// clang++ --std=c++23 -o main