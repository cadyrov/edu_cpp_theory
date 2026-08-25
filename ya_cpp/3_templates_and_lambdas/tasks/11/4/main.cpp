// 4. Напишите `right_subtract` и `left_subtract` и покажите разницу на `8, 2,2`.
#include <cassert>

template <typename... Args> auto right_subtract(Args... args) {
    return (args - ...);
}

template <typename... Args> auto left_subtract(Args... args) {
    return (... - args);
}

int main() {
    assert(right_subtract(8, 2, 2) == 8);
    assert(left_subtract(8, 2, 2) == 4);

    return 0;
}