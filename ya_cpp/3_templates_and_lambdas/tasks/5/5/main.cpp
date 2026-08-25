//5. Напишите шаблон `Power<Base, Exp>` для вычисления степени на этапе компиляции.
#include <cassert>

template <typename T, T Base, int Exp>
class Power {
    private:
        static constexpr T pow(T base, int exp) {
            T result = 1;
            for (int i = 0; i < exp; ++i) {
                result *= base;
            }

            return result;
        }
    public:
        static constexpr T value = Power::pow(Base, Exp);
};

int main() {
    static_assert(Power<int, 4, 5>::value == 1024);
    
    return 0;
}

