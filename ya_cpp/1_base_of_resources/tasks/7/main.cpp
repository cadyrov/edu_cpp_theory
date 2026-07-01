#include <cstring>
#include <utility>

class Matrix {
public:
    Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols), data_(new int[rows * cols]{}) {}

    ~Matrix() { delete[] data_; }

    Matrix(const Matrix &rhd) : rows_(rhd.rows_), cols_(rhd.cols_), data_(new int[rhd.rows_ * rhd.cols_]) {
        std::memcpy(data_, rhd.data_, rows_ * cols_ * sizeof(int));
    }

    Matrix &operator=(const Matrix &rhd) {
        if (this != &rhd) {
            delete[] data_;

            rows_ = rhd.rows_;
            cols_ = rhd.cols_;

            data_ = new int[rhd.rows_ * rhd.cols_];
            std::memcpy(data_, rhd.data_, rows_ * cols_ * sizeof(int));
        }
        return *this;
    }

    Matrix(Matrix &&rhd) noexcept: 
        rows_(std::exchange(rhd.rows_,0)), cols_(std::exchange(rhd.cols_,0)), data_(std::exchange(rhd.data_,nullptr)) {
    }

    Matrix& operator = (Matrix&& rhd) noexcept{
        if (this == &rhd) {
            return *this;
        }

        delete[] data_;

        rows_ = rhd.rows_;
        cols_ = rhd.cols_;

        std::memcpy(data_, rhd.data_, rows_ * cols_ * sizeof(int));
    }

    void swap(Matrix& rhd){
        size_t temp_rows = rows_;
        size_t temp_cols = cols_;
        int* temp_data = data_;

        rows_ = rhd.rows_;
        cols_ = rhd.cols_;
        data_ = rhd.data_;

        rhd.rows_ = temp_rows;
        rhd.cols_ = temp_cols;
        rhd.data_ = temp_data;
    }

    friend void swap(Matrix& lhd, Matrix& rhd){
        lhd.swap(rhd);
    }

private:
    size_t rows_;
    size_t cols_;
    int *data_;
};