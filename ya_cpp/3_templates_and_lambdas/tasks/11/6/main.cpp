// 6. Напишите `all_true` и `any_true` через `&&` и `||`.
#include <cassert>

template <typename... Args> bool all_true(Args... args) {
    return (args && ...);
}

template <typename... Args> bool any_true(Args... args) {
    return (args || ...);
}

int main() {
    assert(all_true(1, 2, 3, 4, 5));
    assert(any_true(1, 0, 0, 0, 0));
    assert(!all_true(1, 0, 0, 0, 0));
    assert(!any_true(0, 0, 0, 0, 0));

    return 0;
}