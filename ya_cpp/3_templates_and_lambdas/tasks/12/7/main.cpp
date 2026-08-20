//  Напишите `id_generator` с захватом `[current = 0]` и `mutable`.

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    auto id_generator = [current = 0]() mutable { return ++current; };

    std::cout << id_generator() << "\n";
    std::cout << id_generator() << "\n";
    return 0;
}