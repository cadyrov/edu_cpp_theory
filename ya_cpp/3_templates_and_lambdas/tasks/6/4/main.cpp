//4.  Передайте объект `Dimensions` как нетиповой параметр шаблона.
#include <cstddef>
#include <string>


class Dimensions{
    public:
        std::size_t rows_;
        std::size_t cols_;
};

template<Dimensions D>
class Image{};

int main() {
    Image<Dimensions{30, 40}> d;

    return 0;
}