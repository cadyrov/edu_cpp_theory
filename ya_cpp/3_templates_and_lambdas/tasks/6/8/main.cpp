//8. Создайте два разных объекта `Dimensions` и проверьте, что типы матриц разные.
#include <cassert>
#include <vector>
#include <cstddef>
#include <type_traits>

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

        static constexpr std::size_t Rows() {
            return D.rows_;
        }

        static constexpr std::size_t Cols() {
            return D.cols_;
        }

    private:
        std::vector<T> data_;
};


int main() {
    static_assert(!std::is_same_v<Matrix<int, Dimensions{4, 5}>, Matrix<int, Dimensions{4, 6}>>);
    
    return 0;
}
