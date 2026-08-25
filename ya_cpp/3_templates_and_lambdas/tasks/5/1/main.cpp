//1. Напишите `StaticArray<T, N>` с массивом размера `N`.
#include <cstddef>

template <typename T, std::size_t N>
class StaticArray{
    public:
    T arr[N]{};
};

int main() {
    StaticArray<int, 3> a;

    return 0;
}