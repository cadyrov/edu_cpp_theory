// 6. Покажите, почему объект с конструктором нельзя корректно создать одним `malloc`.
#include <iostream>
#include <string>

class User {
  public:
    User(int id, std::string name) : id_(id), name_(name) {};
    int GetID() const {
        return id_;
    }
    std::string GetName() const {
        return name_;
    }

  private:
    int id_;
    std::string name_;
};

int main() {
    void* mem = malloc(sizeof(User));
    if (mem == nullptr) {
        return 1;
    }

    User* x = static_cast<User*>(mem);

    std::cout << x->GetID() << " " << x->GetName() << "\n";

    x->~User();

    free(mem);

    return 0;
}

// clang++ --std=c++23 -o main