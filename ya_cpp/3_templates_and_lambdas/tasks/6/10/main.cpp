//10. Напишите пример, где разные значения нетипового параметра создают несовместимые типы.
#include <type_traits>

template<int Val>
class Data{
    public:
    static constexpr int value = Val;
};


int main() {
    static_assert(!std::is_same_v<Data<3>, Data<4>>);

    return 0;
}