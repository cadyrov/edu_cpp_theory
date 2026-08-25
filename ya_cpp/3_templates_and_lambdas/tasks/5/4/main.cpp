//4. Напишите шаблон `LimitChecker<Limit>` с методом `check`.
#include <cstddef>
#include <cassert>

template<typename T, T Limit>
class LimitChecker{
    public:
        bool check(const T& in) {
            return in > T{} && in <= Limit;
        }
};

int main() {
    assert((LimitChecker<int, 5>{}.check(4)));

    return 0;
}