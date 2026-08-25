//Добавьте метод `size`, возвращающий `N`.
#include <cstddef>
#include <cassert>

template <typename T, std::size_t N>
class StaticArray{
public:
    T arr[N]{};

    static std::size_t size() {
        return N;
    }
};

int main() {
    StaticArray<int, 3> a;

    assert(a.size() == 3);

    return 0;
}