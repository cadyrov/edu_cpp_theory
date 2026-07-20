// Напишите `Matrix<T, Rows, Cols>` с хранением `Rows * Cols` элементов.
#include<vector>
#include<utility>
#include<stdexcept>
#include<cassert>

template<typename T,int Rows,int Cols>
class Matrix{
    public:
        Matrix():data_(std::vector<T>{r_*c_}){};

        void Set(const T& in,int x, int y){
            if (x < 0 || x >= Rows || y < 0 || y >= Cols) {
                throw std::exception();
            }

            data_[x*Cols+y] = in;
        }

        const T& Get(int x, int y) const{
            if (x < 0 || x >= Rows || y < 0 || y >= Cols) {
                throw std::exception();
            }

            return data_[x*Cols+y];
        }

    private:
        static const int r_ = Rows;
        static const int c_ = Cols;
        std::vector<T> data_;
};


int main() {
    Matrix<double, 4, 5> b;

    b.Set(4.0, 1, 2);

    assert(b.Get(1, 2) == 4.0);

    
    return 0;
}