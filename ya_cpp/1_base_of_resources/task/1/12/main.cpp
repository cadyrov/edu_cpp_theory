// Переопределите `operator new` и `operator delete` для класса `User` так, чтобы они считали
// количество текущих живых объектов (инкремент в `new`, декремент в `delete`), и проверьте счётчик
// после создания и удаления.
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <new>
#include <stdexcept>

class User {
  public:
    inline static int alive = 0;
    static void* operator new(std::size_t size) {
        void* p = std::malloc(size);
        if (!p) {
            throw std::bad_alloc();
        }

        ++alive;

        return p;
    }

    static void operator delete(void* p) {
        std::free(p);
        --alive;
    }
};

int main() {
    User* u = new User();

    std::cout << User::alive << "\n";
    delete u;
    std::cout << User::alive << "\n";
}

// clang++ --std=c++23 -o main