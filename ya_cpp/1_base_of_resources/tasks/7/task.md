Представьте, что ваш коллега, доктор наук, ускорил алгоритмы для работы с матрицами и уже готовит математическое обоснование операций, которые разработал. 

Чтобы продемонстрировать скорость своих алгоритмов, коллега попросил вас разработать класс Matrix и показать простой пример его использования. 
Скопируйте код ниже к себе и реализуйте:

Две перемещающие операции с помощью одного из инструментов: std::move, std::swap, std::exchange (самостоятельно выберите подходящий).

Метод swap, который не будет использовать перемещающую семантику.

Дружественную функцию swap, которая будет вызываться для вашего класса вместо std::swap.

```cpp
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

    // Ваш код здесь

private:
    size_t rows_;
    size_t cols_;
    int *data_;
};
```

    - Перемещающие операции принимают аргумент по rvalue ref.
    - Перемещающий оператор возвращает ссылку на созданный объект.
    - Дружественная функция может располагаться как внутри, так и снаружи класса.
    - Метод swap принимает аргументы по обычной ссылке и не использует перемещающую семантику.