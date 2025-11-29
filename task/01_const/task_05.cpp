#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// Task 5: Const-correct перегрузка операторов
//
// Реализуй класс Matrix с const-correct перегрузкой операторов.
// Операторы, которые не модифицируют объект, должны быть const, а операторы,
// которые модифицируют, должны быть non-const.
//
// Требования:
// 1. operator+ должен быть const (создаёт новый объект)
// 2. operator+= НЕ должен быть const (модифицирует объект)
// 3. operator* (скалярное умножение) должен иметь const и non-const версии
// 4. operator[] должен иметь const и non-const версии
// 5. Все операторы должны следовать принципам const-correctness

class Matrix {
    std::vector<std::vector<int>> data_;
    size_t rows_;
    size_t cols_;

public:
    Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
        data_.resize(rows, std::vector<int>(cols, 0));
    }
    
    Matrix(std::initializer_list<std::initializer_list<int>> init) {
        rows_ = init.size();
        if (rows_ > 0) {
            cols_ = init.begin()->size();
            for (const auto& row : init) {
                data_.emplace_back(row.begin(), row.end());
            }
        }
    }
    
    // TODO: Implement const operator+
    // Should create new matrix, not modify this
    Matrix operator+(const Matrix& other) const {
        // TODO: implement
        return Matrix(0, 0);
    }
    
    // TODO: Implement non-const operator+=
    // Should modify this matrix
    Matrix& operator+=(const Matrix& other) {
        // TODO: implement
        return *this;
    }
    
    // TODO: Implement const operator* (scalar multiplication, creates new matrix)
    Matrix operator*(int scalar) const {
        // TODO: implement
        return Matrix(0, 0);
    }
    
    // TODO: Implement non-const operator*= (scalar multiplication, modifies this)
    Matrix& operator*=(int scalar) {
        // TODO: implement
        return *this;
    }
    
    // TODO: Implement non-const operator[] (returns non-const row reference)
    std::vector<int>& operator[](size_t row) {
        // TODO: implement
        static std::vector<int> dummy;
        return dummy;
    }
    
    // TODO: Implement const operator[] (returns const row reference)
    const std::vector<int>& operator[](size_t row) const {
        // TODO: implement
        static const std::vector<int> dummy;
        return dummy;
    }
    
    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }
};

void testMatrix() {
    Matrix m1{{1, 2}, {3, 4}};
    const Matrix m2{{5, 6}, {7, 8}};
    
    // These should compile:
    Matrix m3 = m1 + m2;           // Const operator+ on non-const object
    Matrix m4 = m2 + m1;           // Const operator+ on const object
    m1 += m2;                      // Non-const operator+=
    Matrix m5 = m1 * 2;            // Const operator* (creates new)
    m1 *= 3;                       // Non-const operator*=
    m1[0][0] = 100;                // Non-const operator[]
    int val = m2[0][0];            // Const operator[]
    
    // These should NOT compile:
    // m2 += m1;                    // Error: cannot modify const object
    // m2 *= 2;                     // Error: cannot modify const object
    // m2[0][0] = 200;              // Error: cannot modify through const operator[]
    // m2[0] = std::vector<int>();  // Error: cannot modify through const operator[]
}

int main() {
    testMatrix();
    return 0;
}

