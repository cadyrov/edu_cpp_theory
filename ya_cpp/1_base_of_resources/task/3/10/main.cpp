/*
10. Напишите `unique_ptr` с custom deleter для `FILE*`.
*/
#include <iostream>
#include <memory>

int main() {
    auto lmb = [](FILE* in) noexcept {
        if (in == nullptr) {
            return;
        }

        std::fclose(in);
    };

    auto p = std::unique_ptr<FILE, decltype(lmb)>();
}