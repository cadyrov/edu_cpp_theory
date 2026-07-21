//5. Напишите `Matrix<T, dims>`, где размер берется из `dims.rows * dims.cols`.
#include <cassert>
#include <vector>
#include <cstddef>

class Dimensions{
    public:
        std::size_t rows_;
        std::size_t cols_;
};

template<typename T, Dimensions D>
class Matrix{
    public:
        Matrix():data_(std::vector<T>(D.cols_ * D.rows_)){};

        static constexpr std::size_t Size() {
            return D.cols_ * D.rows_;
        }   

    private:
        std::vector<T> data_;
};


int main() {
    static_assert(Matrix<int, Dimensions{4, 5}>::Size() == 20);
    
    return 0;
}
