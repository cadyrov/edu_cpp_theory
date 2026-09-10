#include <iostream>
#include <memory>
#include <stdexcept>
/*
1. Напишите пример утечки памяти без `delete`.
2. Напишите пример утечки при раннем `return`.
3. Напишите пример утечки при исключении между `new` и `delete`.
4. Исправьте утечку через `try/catch` и ручной `delete`.
5. Покажите, почему такой ручной код сложно поддерживать.
*/

void delete_leak() {
    auto p = new int(1);
}

void early_return(bool in) {
    auto p = new int(1);
    if (in == true) {
        return;
    }

    delete p;
}

void excepton_leak() {

    try {
        auto p = new int(1);

        throw std::bad_alloc();

        delete p;
    } catch (const std::exception e) {
        std::cout << e.what() << "\n";
    }
}

void excepton_leak_fix() {
    auto p = new int(1);
    try {
        throw std::bad_alloc();

        delete p;
    } catch (const std::exception e) {
        if (p != nullptr) {
            delete p;
        }

        std::cout << e.what() << "\n";
    }
}

/*
6. Напишите функцию с двумя ресурсами, где второй `new` может бросить исключение.
7. Исправьте пример через локальные объекты стандартной библиотеки.
8. Напишите пример double delete.
9. Напишите пример dangling pointer после `delete`.
10. Сформулируйте правило: кто владеет указателем и кто обязан освобождать.
*/

class BadRes {
  public:
    BadRes() {
        throw std::bad_alloc();
    };
};

void doubleres() {
    auto p = new int(33);
    BadRes* bad = new BadRes();

    delete p;
    delete bad;
}

void doubleres() {
    auto p = new int(33);
    BadRes* bad = new BadRes();

    delete p;
    delete bad;
}

void doubleresfix() {
    auto p = std::make_unique<int>(33);
    auto bad = std::make_unique<BadRes>();
}

void doubledelete() {
    auto p = new int(33);

    delete p;
    delete p;
}

void dangling() {
    auto p = new int(33);

    delete p;
    *p = 44;
}

int main() {
    std::cout << 1 << "\n";

    return 0;
}

// clang++ --std=c++23 -o main