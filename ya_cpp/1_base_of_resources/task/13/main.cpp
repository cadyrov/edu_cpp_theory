// Переопределите `operator new` и `operator delete` для класса `User` так, чтобы они считали
// количество текущих живых объектов (инкремент в `new`, декремент в `delete`), и проверьте счётчик
// после создания и удаления.
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <new>
#include <stdexcept>

struct User {
    static void* operator new(std::size_t) {
        throw std::bad_alloc();
    }

    static void* operator new(std::size_t, const std::nothrow_t&) noexcept {
        return nullptr;
    }
};

int main() {
    try {
        User* p = new User();
        delete p;
    } catch (const std::bad_alloc&) {
        std::cout << "bad_alloc\n";
    }

    User* p = new (std::nothrow) User();
    if (!p) {
        std::cout << "nullptr\n";
    }
    delete p; // для nullptr безопасно
}

// clang++ --std=c++23 -o main