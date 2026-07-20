//1. Напишите шаблон `EpsilonCompare<T, epsilon>`.
#include <cassert>
#include <cmath>

template <typename T, T epsilon = static_cast<T>(.00001)>
class EpsilonCompare{
    public:
    static bool Compare(const T& a,const T& b) {
        return std::abs(a - b) < epsilon;
    } 
};

int main() {
    assert((!EpsilonCompare<double>::Compare(.1, .2)));

    return 0;
}